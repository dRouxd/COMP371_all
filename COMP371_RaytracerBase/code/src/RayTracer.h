#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "SphereObject.h"
#include "RectangleObject.h"
#include "LightObject.h"
#include "Output.h"
#include "Ray.h"

#include "json.hpp"

#include <vector>

class RGB;

class RayTracer
{
public:
    RayTracer(nlohmann::json j);
    ~RayTracer();

    void run();

private:

    void outputBufferToPPM(std::string outputFilename, Eigen::Vector3f** buf, unsigned int w, unsigned int h);
    
    GeometricObject* rayIntersectObjects(Ray* ray, float& dist);
    float rayIntersectSphere(Ray* ray, SphereObject* so);
    float rayIntersectRect(Ray* ray, RectangleObject* ro);
    void calcRayColor(Ray* ray, GeometricObject* o, float oDist, Output* out);
    void calcRayColorLocal(Ray* ray, GeometricObject* o, float oDist, Output* out);
    void calcRayColorGlobal(Ray* ray, GeometricObject* o, float oDist, Output* out);
    RGB calcBSDF(Eigen::Vector3f p, Ray* ray, GeometricObject* o, LightObject* l);

    std::vector<GeometricObject*> geometricObjects;
    std::vector<LightObject*> lightObjects;
    std::vector<Output*> outputs;

};

#endif