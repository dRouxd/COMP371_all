#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "SphereObject.h"
#include "RectangleObject.h"
#include "LightObject.h"
#include "Output.h"
#include "Ray.h"

#include "json.hpp"

#include <vector>

class RayTracer
{
public:
    RayTracer(nlohmann::json j);
    ~RayTracer();

    void run();

private:

    void outputBufferToPPM(std::string outputFilename, Eigen::Vector3f** buf, unsigned int w, unsigned int h);
    
    bool rayIntersectObjects(Ray* ray);
    float rayIntersectSphere(Ray* ray, SphereObject* so);
    float rayIntersectRect(Ray* ray, RectangleObject* ro);

    std::vector<GeometricObject*> geometricObjects;
    std::vector<LightObject*> lightObjects;
    std::vector<Output*> outputs;

};

#endif