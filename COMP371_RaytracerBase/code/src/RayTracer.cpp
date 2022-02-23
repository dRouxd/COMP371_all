
#include "RayTracer.h"

#include "RectangleObject.h"
#include "SphereObject.h"
#include "PointObject.h"
#include "AreaObject.h"
#include "util.hpp"

#include <Eigen/Dense>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

RayTracer::RayTracer(nlohmann::json j)
{
    nlohmann::json geometries = j["geometry"];
    for(auto it = geometries.begin(); it != geometries.end(); ++it)
    {
        GeometricObject* go = CreateGeometricObjectFromJson(it.value());
        this->geometricObjects.push_back(go);
    }

    nlohmann::json lights = j["light"];
    for(auto it = lights.begin(); it != lights.end(); ++it)
    {
        LightObject* lo = CreateLightObjectFromJson(it.value());
        this->lightObjects.push_back(lo);
    }

    nlohmann::json outputs = j["output"];
    for(auto it = outputs.begin(); it != outputs.end(); ++it)
    {
        Output* lo = new Output(it.value());
        this->outputs.push_back(lo);
    }
}

RayTracer::~RayTracer()
{
    for(auto o : this->geometricObjects)
    {
        delete o;
    }

    for(auto l : this->lightObjects)
    {
        delete l;
    }

    for(auto o : this->outputs)
    {
        delete o;
    }
}

void RayTracer::run()
{
    // Export image for every output
    for(auto it = this->outputs.begin(); it != this->outputs.end(); ++it)
    {
        Output* currentOut = (*it);
        Camera* camera = currentOut->getCamera();

        // Create the buffer used to output to ppm
        Eigen::Vector3f** buf = new Eigen::Vector3f*[camera->getHeight()];
        for(int i = 0; i < camera->getHeight(); ++i)
        {
            buf[i] = new Eigen::Vector3f[camera->getWidth()];
        }

        // For every pixel
        for(int x = 0; x < camera->getHeight(); ++x)
        {
            for(int y = 0; y < camera->getWidth(); ++y)
            {
                // Create a ray at the center of the pixel
                Ray* r = CreateRayFromCamera(camera, x, y);

                float distToHit = -1.0f;
                GeometricObject* oHit = rayIntersectObjects(r, distToHit);

                if(oHit)
                {
                    calculateRayColorOnObject(r, oHit, distToHit, currentOut);
                    buf[x][y] << r->getColor()(0), r->getColor()(1), r->getColor()(2);
                }
                else
                    buf[x][y] << currentOut->getBKC()(0), currentOut->getBKC()(1), currentOut->getBKC()(2);

                // Assign the color of that ray to the corresponding pixel
                //Eigen::Vector3f c = r->getColor();
                //buf[x][y] << c.coeff(0), c.coeff(1), c.coeff(2);

                delete r;
            }
        }

        outputBufferToPPM(currentOut->getOutputFilename(), buf, camera->getWidth(), camera->getHeight());

        for(int i = 0; i < camera->getHeight(); ++i)
        {
            delete[] buf[i];
        }
        delete[] buf;
    }
}

void RayTracer::outputBufferToPPM(std::string outputFilename, Eigen::Vector3f** buf, unsigned int w, unsigned int h)
{
    std::ofstream ofs(outputFilename, std::ios_base::out | std::ios_base::binary);
    ofs << "P6" << std::endl << w << ' ' << h << std::endl << "255" << std::endl;

    for (unsigned int j = 0; j < h; ++j)
        for (unsigned int i = 0; i < w; ++i)
        {
            ofs << (char) (255.0 * buf[i][j](0));
            ofs << (char) (255.0 * buf[i][j](1));
            ofs << (char) (255.0 * buf[i][j](2));
        }

    ofs.close();
}

GeometricObject* RayTracer::rayIntersectObjects(Ray* ray, float& dist)
{
    GeometricObject* closestObject = NULL;
    float closestDist = -1.0;

    // Find the first object which is hit by the ray
    for(auto o : this->geometricObjects)
    {
        float distToObject = -1.0;
        if(o->getType() == ObjectType::Sphere)
        {
            SphereObject* so = dynamic_cast<SphereObject*>(o);
            distToObject = rayIntersectSphere(ray, so);
        }

        if(o->getType() == ObjectType::Rectangle)
        {
            RectangleObject* ro = dynamic_cast<RectangleObject*>(o);
            distToObject = rayIntersectRect(ray, ro);
        }
        
        if(distToObject >= 0 && (!closestObject || distToObject < closestDist))
        {
            closestObject = o;
            closestDist = distToObject;
        }
    }

    dist = closestDist;
    return closestObject;
}

float RayTracer::rayIntersectSphere(Ray* ray, SphereObject* so)
{
    float dist = -1.0;

    Eigen::Vector3f L = so->getCentre() - ray->getOrigin();
    float ld = L.dot(ray->getDirection());
    if(ld < 0)
        return dist;

    float lld = sqrt(L.dot(L) - ld * ld);
    if(lld >= so->getRadius())
        return dist;

    float rlld = sqrt(pow(so->getRadius(), 2) - lld*lld);

    // Sphere intersection points
    float t0 = ld - rlld;
    float t1 = ld + rlld;

    // If sphere is ahead of camera
    if(t0 > 0 && t1 > 0)
        dist = t0;

    // If camera is in sphere
    else if(t0 < 0 && t1 > 0)
        dist = t1;

    return dist;

}

float RayTracer::rayIntersectRect(Ray* ray, RectangleObject* ro)
{
    Eigen::Vector3f N = ro->getNormal();
    float dist = -1.0;
    
    float a = N.dot(ray->getDirection());

    // Is the ray and the plane parallel?
    if (std::fpclassify(fabs(a)) == FP_ZERO)
        return dist;

    float t = N.dot(ro->getP1() - ray->getOrigin()) / a;

    // Is the plan behind the ray?
    if(t < 0)
        return dist;

    Eigen::Vector3f p = ray->getOrigin() + t * ray->getDirection();

    // Is the point inside the rectangle?
    Eigen::Vector3f e1 = ro->getP2() - ro->getP1();
    Eigen::Vector3f e2 = ro->getP3() - ro->getP2();
    Eigen::Vector3f e3 = ro->getP4() - ro->getP3();
    Eigen::Vector3f e4 = ro->getP1() - ro->getP4();

    Eigen::Vector3f c1 = p - ro->getP1();
    Eigen::Vector3f c2 = p - ro->getP2();
    Eigen::Vector3f c3 = p - ro->getP3();
    Eigen::Vector3f c4 = p - ro->getP4();

    if( N.dot(e1.cross(c1)) > 0 &&
        N.dot(e2.cross(c2)) > 0 &&
        N.dot(e3.cross(c3)) > 0 &&
        N.dot(e4.cross(c4)) > 0)
        dist = t;

    return dist;
}

void RayTracer::calculateRayColorOnObject(Ray* ray, GeometricObject* o, float oDist, Output* out)
{
    // Offset by small value to remove numerical imprecision.
    Eigen::Vector3f point = ray->getOrigin() + (oDist - 0.00001) * ray->getDirection();
    Eigen::Vector3f normalFromObject;
    if(o->getType() == ObjectType::Rectangle)
        normalFromObject = dynamic_cast<RectangleObject*>(o)->getNormal();
    else
    {
        normalFromObject = CreateNormalFrom2Points(dynamic_cast<SphereObject*>(o)->getCentre(), point);
    }

    // Ambiant component
    float LRa = o->getKA() * o->getAC()(0) * out->getAI()(0);
    float LGa = o->getKA() * o->getAC()(1) * out->getAI()(0);
    float LBa = o->getKA() * o->getAC()(2) * out->getAI()(0);

    // Combine all components
    float LR = LRa;// + LRd + LRs;
    float LG = LGa;// + LGd + LGs;
    float LB = LBa;// + LBd + LBs;

    for(auto l : this->lightObjects)
    {
        PointObject* light = dynamic_cast<PointObject*>(l);
        Eigen::Vector3f lightDirection = CreateNormalFrom2Points(point, light->getCentre());
        
        // Check if there's any objects in the path of to the light
        Ray* rayToLight = new Ray(point, lightDirection);
        float tmp = -1.0f;
        GeometricObject* lightObstructed = rayIntersectObjects(rayToLight, tmp);
        delete rayToLight;
        
        if(lightObstructed)
            continue;
        
        // I: Intensity of the light for each color
        float IR = light->getIS()(0) * light->getID()(0);
        float IG = light->getIS()(1) * light->getID()(1);
        float IB = light->getIS()(2) * light->getID()(2);

        // Diffuse component of the color value
        float maxD = std::max(0.0f, normalFromObject.dot(lightDirection));
        float LRd = (o->getKD() * o->getDC()(0)) * maxD;
        float LGd = (o->getKD() * o->getDC()(1)) * maxD;
        float LBd = (o->getKD() * o->getDC()(2)) * maxD;

        // Specular component of the color value
        Eigen::Vector3f v = CreateNormalFrom2Points(point, ray->getOrigin());
        Eigen::Vector3f R = (2.0f * normalFromObject * (normalFromObject.dot(lightDirection)) - lightDirection);
        Eigen::Vector3f H = (ray->getDirection() + v) / (ray->getDirection() + v).norm();
        float maxS = std::pow(std::max(0.0f, R.dot(v)), o->getPC());
        float LRs = (o->getKS() * o->getSC()(0)) * maxS;
        float LGs = (o->getKS() * o->getSC()(1)) * maxS;
        float LBs = (o->getKS() * o->getSC()(2)) * maxS;

        LR += IR * (LRd + LRs);
        LG += IG * (LGd + LGs);
        LB += IB * (LBd + LBs);
    }

    // Clamp light value between 0 and 1
    LR = std::min(LR, 1.0f);
    LG = std::min(LG, 1.0f);
    LB = std::min(LB, 1.0f);

    Eigen::Vector3f rayColor(LR, LG, LB);
    ray->setColor(rayColor);
}