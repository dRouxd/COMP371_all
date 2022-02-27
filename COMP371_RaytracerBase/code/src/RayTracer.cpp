
#include "RayTracer.h"

#include "PointLight.h"
#include "AreaLight.h"
#include "util.hpp"
#include "RGB.h"

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
        Geometric* go = CreateGeometricObjectFromJson(it.value());
        this->geometricObjects.push_back(go);
    }

    nlohmann::json lights = j["light"];
    for(auto it = lights.begin(); it != lights.end(); ++it)
    {
        Light* lo = CreateLightObjectFromJson(it.value());
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
        for(int y = 0; y < camera->getHeight(); ++y)
        {
            for(int x = 0; x < camera->getWidth(); ++x)
            {
                // Create a ray at the center of the pixel
                Ray* r = CreateRayFromCamera(camera, x, y);

                // Check if the ray hits any objects
                float distToHit = -1.0f;
                Object* oHit = rayIntersectObjects(r, distToHit);
                if(oHit)
                {
                    calcRayColor(r, oHit, distToHit, currentOut);
                    buf[y][x] << r->getColor()(0), r->getColor()(1), r->getColor()(2);
                }
                else
                    buf[y][x] << currentOut->getBKC()(0), currentOut->getBKC()(1), currentOut->getBKC()(2);

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

    for (unsigned int y = 0; y < h; ++y)
        for (unsigned int x = 0; x < w; ++x)
        {
            ofs << (char) (255.0 * buf[y][x](0));
            ofs << (char) (255.0 * buf[y][x](1));
            ofs << (char) (255.0 * buf[y][x](2));
        }
    ofs.close();
}

Object* RayTracer::rayIntersectObjects(Ray* ray, float& dist)
{
    Object* closestObject = NULL;
    float closestDist = -1.0;

    // Find the first object or light which is hit by the ray
    for(auto o : this->geometricObjects)
    {
        float distToObject = -1.0;
        if(o->getType() == ObjectType::Sphere)
        {
            SphereGeom* so = dynamic_cast<SphereGeom*>(o);
            distToObject = rayIntersectSphere(ray, so);
        }

        if(o->getType() == ObjectType::Rectangle)
        {
            RectangleGeom* ro = dynamic_cast<RectangleGeom*>(o);
            distToObject = rayIntersectRect(ray, ro);
        }
        
        if(distToObject >= 0 && (!closestObject || distToObject < closestDist))
        {
            closestObject = o;
            closestDist = distToObject;
        }
    }

    for(auto l : this->lightObjects)
    {
        float distToObject = -1.0;
        if(l->getType() == ObjectType::Area)
        {
            AreaLight* al = dynamic_cast<AreaLight*>(l);
            distToObject = rayIntersectRect(ray, al);
        }
        
        if(distToObject >= 0 && (!closestObject || distToObject < closestDist))
        {
            closestObject = l;
            closestDist = distToObject;
        }
    }

    dist = closestDist;
    return closestObject;
}

float RayTracer::rayIntersectSphere(Ray* ray, SphereGeom* so)
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

float RayTracer::rayIntersectRect(Ray* ray, Rectangle* r)
{
    float dist = -1.0;

    Eigen::Vector3f N = r->getNormal();
    
    float a = N.dot(ray->getDirection());

    // Is the ray and the plane parallel?
    if (std::fpclassify(fabs(a)) == FP_ZERO)
        return dist;

    float t = N.dot(r->getP1() - ray->getOrigin()) / a;

    // Is the plane behind the ray?
    if(t < 0)
        return dist;

    Eigen::Vector3f p = ray->getOrigin() + t * ray->getDirection();

    // Is the point inside the rectangle?
    Eigen::Vector3f e1 = r->getP2() - r->getP1();
    Eigen::Vector3f e2 = r->getP3() - r->getP2();
    Eigen::Vector3f e3 = r->getP4() - r->getP3();
    Eigen::Vector3f e4 = r->getP1() - r->getP4();

    Eigen::Vector3f c1 = p - r->getP1();
    Eigen::Vector3f c2 = p - r->getP2();
    Eigen::Vector3f c3 = p - r->getP3();
    Eigen::Vector3f c4 = p - r->getP4();

    if( N.dot(e1.cross(c1)) > 0 &&
        N.dot(e2.cross(c2)) > 0 &&
        N.dot(e3.cross(c3)) > 0 &&
        N.dot(e4.cross(c4)) > 0)
        dist = t;

    return dist;
}

void RayTracer::calcRayColor(Ray* ray, Object* o, float oDist, Output* out)
{
    if(out->getGlobalIllum())
        calcRayColorGlobal(ray, o, oDist, out);
    else
        calcRayColorLocal(ray, o, oDist, out);
}

void RayTracer::calcRayColorLocal(Ray* ray, Object* o, float oDist, Output* out)
{
    // Offset by small value to remove numerical imprecision.
    Eigen::Vector3f point = ray->getOrigin() + (oDist - 0.001) * ray->getDirection();

    // If the ray hits the area light, get the light value directly
    if(o->getType() == ObjectType::Area)
    {
        AreaLight* al = dynamic_cast<AreaLight*>(o);
        RGB c(al->getLightColor());
        c.clamp();

        ray->setColor(c);
        return;
    }else if(o->getType() == ObjectType::Point)
    {
        return;
    }

    Geometric* geom = dynamic_cast<Geometric*>(o);

    // Ambiant component
    RGB L(geom->getKA() * geom->getAC()(0) * out->getAI()(0), 
            geom->getKA() * geom->getAC()(1) * out->getAI()(0), 
            geom->getKA() * geom->getAC()(2) * out->getAI()(0));

    L += calcBSDF(point, ray, geom);
    
    // Clamp light value between 0 and 1
    L.clamp();

    ray->setColor(L);
}

void RayTracer::calcRayColorGlobal(Ray* ray, Object* o, float oDist, Output* out)
{
    
}

RGB RayTracer::calcBSDF(Eigen::Vector3f p, Ray* r, Geometric* o)
{
    Eigen::Vector3f normalFromObject;
    if(o->getType() == ObjectType::Rectangle)
    {
        normalFromObject = dynamic_cast<RectangleGeom*>(o)->getNormal();
    } else
    {
        normalFromObject = CreateNormalFrom2Points(dynamic_cast<SphereGeom*>(o)->getCentre(), p);
    }

    if(normalFromObject.dot(r->getDirection()) > 0)
        normalFromObject = -normalFromObject;

    RGB L;

    // Calculate BSDF for every lights in the scene
    for(auto l : this->lightObjects)
    {
        Eigen::Vector3f lightDirection;
        
        // I: Intensity of the light
        RGB IL(l->getLightColor());

        // TODO: if point light, keep that, otherwise do monte carlo integration on area light
        if(l->getType() == ObjectType::Point)
        {
            PointLight* po = dynamic_cast<PointLight*>(l);
            lightDirection = CreateNormalFrom2Points(p, po->getCentre());
            
            // Check if there's any objects in the path of to the light
            Ray* rayToLight = new Ray(p, lightDirection);
            float distToObs = -1.0f;
            Object* lightObstructed = rayIntersectObjects(rayToLight, distToObs);
            delete rayToLight;
            
            if(lightObstructed && distToObs < GetDistanceBetween2Points(p, po->getCentre()))
            {
                // If the obstructed object is an area light, use the area light intensity for the calculations
                if(lightObstructed->getType() == ObjectType::Area)
                {
                    AreaLight* al = dynamic_cast<AreaLight*>(lightObstructed);
                    IL = al->getLightColor();
                }else
                    continue;
            }
        }

        // Diffuse component of the color value
        float maxD = std::max(0.0f, normalFromObject.dot(lightDirection));
        RGB ID(o->getKD() * o->getDC() * maxD);

        // Specular component of the color value
        Eigen::Vector3f v = CreateNormalFrom2Points(p, r->getOrigin());
        Eigen::Vector3f R = (2.0f * normalFromObject * (normalFromObject.dot(lightDirection)) - lightDirection);
        Eigen::Vector3f H = (v + lightDirection).normalized();
        float maxS = std::pow(std::max(0.0f, normalFromObject.dot(H)), o->getPC());
        RGB IS(o->getKS() * o->getSC() * maxS);

        L += IL * (ID + IS);
    }

    return L;
}