#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "SphereGeom.h"
#include "RectangleGeom.h"
#include "Light.h"
#include "Rectangle.h"
#include "Output.h"
#include "Ray.h"

#include "json.hpp"

#include <vector>

class RGB;
class Rectangle;

class RayTracer
{
public:
    RayTracer(nlohmann::json j);
    ~RayTracer();

    void run();

private:

    void outputBufferToPPM(std::string outputFilename, Eigen::Vector3f** buf, unsigned int w, unsigned int h);
    
    Object* rayIntersectObjects(Ray* ray, float& dist);
    float rayIntersectSphere(Ray* ray, SphereGeom* so);
    float rayIntersectRect(Ray* ray, Rectangle* ro);
    void calcRayColor(Ray* ray, Object* o, float oDist, Output* out);
    void calcRayColorLocal(Ray* ray, Object* o, float oDist, Output* out);
    void calcRayColorGlobal(Ray* ray, Object* o, float oDist, Output* out);
    RGB calcBSDF(Eigen::Vector3f p, Ray* ray, Geometric* o);

    std::vector<Geometric*> geometricObjects;
    std::vector<Light*> lightObjects;
    std::vector<Output*> outputs;

};

#endif