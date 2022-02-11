#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "GeometricObject.h"
#include "LightObject.h"
#include "Output.h"

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

    std::vector<GeometricObject*> geometricObjects;
    std::vector<LightObject*> lightObjects;
    std::vector<Output*> outputs;

};

#endif