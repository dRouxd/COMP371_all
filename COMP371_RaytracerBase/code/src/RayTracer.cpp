
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
#include <random>

#define EPSILON 0.001
#define AREALIGHT_MAX_SAMPLING 4

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
            distToObject = so->rayIntersect(ray);
        }

        if(o->getType() == ObjectType::Rectangle)
        {
            RectangleGeom* ro = dynamic_cast<RectangleGeom*>(o);
            distToObject = ro->rayIntersect(ray);
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
            distToObject = al->rayIntersect(ray);
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
    Eigen::Vector3f point = ray->getOrigin() + (oDist - EPSILON) * ray->getDirection();

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
    RGB L(geom->getAmbiantColor());

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
        normalFromObject = dynamic_cast<SphereGeom*>(o)->getNormalFromPointOnSphere(p);
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
            PointLight* pl = dynamic_cast<PointLight*>(l);
            lightDirection = CreateNormalFrom2Points(p, pl->getCentre());
            
            // Check if there's any objects in the path of to the light
            Ray* rayToLight = new Ray(p, lightDirection);
            float distToObst = -1.0f;
            Object* lightObstructed = rayIntersectObjects(rayToLight, distToObst);
            delete rayToLight;
            
            if(lightObstructed && distToObst < GetDistanceBetween2Points(p, pl->getCentre()))
            {
                // If the obstructed object is an area light, use the area light intensity for the calculations
                if(lightObstructed->getType() == ObjectType::Area)
                {
                    AreaLight* al = dynamic_cast<AreaLight*>(lightObstructed);
                    IL = al->getLightColor();
                }else
                    continue;
            }
        }else
        {
            AreaLight* al = dynamic_cast<AreaLight*>(l);

            Eigen::Vector3f lightAverageLocation = Eigen::Vector3f::Zero();
            RGB lightAverageIntensity;

            Eigen::Vector3f p1p2 = al->getP2() - al->getP1();
            Eigen::Vector3f p1p4 = al->getP4() - al->getP1();
            float p1p2Len = (p1p2.norm() - 2*EPSILON) / AREALIGHT_MAX_SAMPLING;
            float p1p4Len = (p1p4.norm() - 2*EPSILON) / AREALIGHT_MAX_SAMPLING;
    
            std::random_device rd; 
            std::default_random_engine eng(rd());
            std::uniform_real_distribution<float> dist(0.0f, 1.0f);

            float slopei = 1.0f / (p1p2.norm() - EPSILON);
            float slopej = 1.0f / (p1p4.norm() - EPSILON);

            // Sample the area light many times
            for(int i = 0; i < AREALIGHT_MAX_SAMPLING; ++i)
            {
                for(int j = 0; j < AREALIGHT_MAX_SAMPLING; ++j)
                {
                    float randi = (EPSILON + p1p2Len*i + dist(eng)*p1p2Len);
                    float randj = (EPSILON + p1p4Len*j + dist(eng)*p1p4Len);

                    randi = slopei * (randi - EPSILON);
                    randj = slopej * (randj - EPSILON);

                    Eigen::Vector3f randPoint(al->getP1() + randi * p1p2 + randj * p1p4);
                    Eigen::Vector3f vectToRandPoint = CreateNormalFrom2Points(p, randPoint);
                    
                    Ray* rayToLight = new Ray(p, vectToRandPoint);
                    float distToObst = -1;
                    Object* lightObstructed = rayIntersectObjects(rayToLight, distToObst);
                    delete rayToLight;

                    // If there's nothing blocking the ray to the area light, add this ray to the calculation
                    if(distToObst >= GetDistanceBetween2Points(p, randPoint) - EPSILON)
                    {
                        lightAverageLocation += randPoint;
                        lightAverageIntensity += l->getLightColor();
                    }
                }
            }

            IL = lightAverageIntensity / (AREALIGHT_MAX_SAMPLING * AREALIGHT_MAX_SAMPLING);
            lightAverageLocation = lightAverageLocation / (AREALIGHT_MAX_SAMPLING * AREALIGHT_MAX_SAMPLING);
            lightDirection = CreateNormalFrom2Points(p, lightAverageLocation);
        }

        // Diffuse component of the color value
        float maxD = std::max(0.0f, normalFromObject.dot(lightDirection));
        RGB ID(o->getDiffuseColor() * maxD);

        // Specular component of the color value
        Eigen::Vector3f v = CreateNormalFrom2Points(p, r->getOrigin());
        Eigen::Vector3f R = (2.0f * normalFromObject * (normalFromObject.dot(lightDirection)) - lightDirection);
        Eigen::Vector3f H = (v + lightDirection).normalized();
        float maxS = std::pow(std::max(0.0f, normalFromObject.dot(H)), o->getPC());
        RGB IS(o->getSpecularColor() * maxS);

        L += IL * (ID + IS);
    }

    return L;
}