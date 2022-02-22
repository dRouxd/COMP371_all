
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
    /*for(auto it = this->geometricObjects.begin(); it != this->geometricObjects.end(); ++it)
    {
        (*it)->print();
        std::cout << std::endl;
    }
    

    for(auto it = this->lightObjects.begin(); it != this->lightObjects.end(); ++it)
    {
        (*it)->print();
        std::cout << std::endl;
    }*/


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

                if(rayIntersectObjects(r))
                    buf[x][y] << r->getColor()(0), r->getColor()(1), r->getColor()(2);
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

bool RayTracer::rayIntersectObjects(Ray* ray)
{
    GeometricObject* closestObject = NULL;
    float closestDist = -1.0;

    for(auto o : this->geometricObjects)
    {
        if(o->getType() == ObjectType::Sphere)
        {
            SphereObject* so = dynamic_cast<SphereObject*>(o);

            Eigen::Vector3f p;
            float distToObject = rayIntersectSphere(ray, so, p);
            if(distToObject >= 0 && (!closestObject || distToObject < closestDist))
            {
                closestObject = so;
                closestDist = distToObject;
            }
        }
    }

    if(closestObject)
    {
        ray->setColor(closestObject->getDC());
        Eigen::Vector3f point = ray->getOrigin() + closestDist * ray->getDirection();
    }

    return closestDist >= 0;
}

float RayTracer::rayIntersectSphere(Ray* ray, SphereObject* so)
{
    // Tutorial: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
    float dist = -1.0;

    Eigen::Vector3f L = so->getCentre() - ray->getOrigin();
    float tca = L.dot(ray->getDirection());
    if(tca < 0)
        return dist;

    float d = sqrt(L.dot(L) - tca * tca);
    if(d >= so->getRadius())
        return dist;

    float thc = sqrt(pow(so->getRadius(), 2) - d*d);

    // Sphere intersection points
    float t0 = tca - thc;
    float t1 = tca + thc;

    // If sphere is ahead of camera
    if(t0 > 0 && t1 > 0)
        dist = t0;

    // If camera is in sphere
    else if(t0 < 0 && t1 > 0)
        dist = t1;

    return dist;

}