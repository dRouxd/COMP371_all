
#include "RayTracer.h"
#include "RectangleObject.h"
#include "SphereObject.h"

#include "PointObject.h"
#include "AreaObject.h"

#include "CameraObject.h"

#include "util.hpp"

#include <iostream>
#include <fstream>
#include <vector>

RayTracer::RayTracer(nlohmann::json j)
{
    //
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
}

void RayTracer::run()
{
    /*for(auto it = this->geometricObjects.begin(); it != this->geometricObjects.end(); ++it)
    {
        std::cout << (*(*it)) << std::endl;
        if((*it)->getType() == Rectangle)
        {
            RectangleObject* ro = dynamic_cast<RectangleObject*>((*it));
            std::cout << (*ro) << std::endl;
        }
        else if((*it)->getType() == Sphere)
        {
            SphereObject* so = dynamic_cast<SphereObject*>((*it));
            std::cout << (*so) << std::endl;
        }
        std::cout << std::endl;
    }
    

    for(auto it = this->lightObjects.begin(); it != this->lightObjects.end(); ++it)
    {
        std::cout << (*(*it)) << std::endl;
        if((*it)->getType() == Point)
        {
            PointObject* ro = dynamic_cast<PointObject*>((*it));
            std::cout << (*ro) << std::endl;
        }
        else if((*it)->getType() == Area)
        {
            AreaObject* so = dynamic_cast<AreaObject*>((*it));
            std::cout << (*so) << std::endl;
        }
        std::cout << std::endl;
    }*/


    // Output an image for every output
    for(auto it = this->outputs.begin(); it != this->outputs.end(); ++it)
    {
        Output* currentOut = (*it);
        CameraObject* camera = currentOut->getCamera();

        // Create the buffer used to output to ppm
        Eigen::Vector3f** buf = new Eigen::Vector3f*[camera->getHeight()];
        for(int i = 0; i < camera->getHeight(); ++i)
        {
            buf[i] = new Eigen::Vector3f[camera->getWidth()];
        }

        buf[100][200] << 1, 0, 0;
        buf[100][300] << 0, 1, 0;
        buf[100][400] << 0, 0, 1;
        buf[250][250] << 0.5, 0.5, 0.5;

        outputBufferToPPM(currentOut->getOutputFilename(), buf, camera->getWidth(), camera->getHeight());
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