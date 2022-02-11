
#include "RayTracer.h"
#include "RectangleObject.h"
#include "SphereObject.h"

#include "PointObject.h"
#include "AreaObject.h"

#include "CameraObject.h"

#include "util.hpp"

#include <iostream>
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
    for(auto it = this->geometricObjects.begin(); it != this->geometricObjects.end(); ++it)
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
    }

    for(auto it = this->outputs.begin(); it != this->outputs.end(); ++it)
    {
        
    }
}