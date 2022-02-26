#ifndef OUTPUT_H
#define OUTPUT_H

#include "Camera.h"

#include "json.hpp"

#include <Eigen/Core>

class Output
{
public:
    Output(nlohmann::json j);
    ~Output();

    inline std::string getOutputFilename() const { return outputFilename; };
    inline Camera* getCamera() const { return camera; };
    inline Eigen::Vector3f getAI() const { return ai; };
    inline Eigen::Vector3f getBKC() const { return bkc; };
    inline unsigned int* getRaysPerPixel() const { return raysPerPixel; };
    inline unsigned int getRaysPerPixelSize() const { return raysPerPixelSize; };
    inline unsigned int getSpeedup() const { return speedup; };
    inline bool getAntialias() const { return antialiasing; };
    inline bool getTwoSiseRender() const { return twosiderender; };
    inline bool getGlobalIllum() const { return globalillum; };

private:
    std::string outputFilename;
    Camera* camera;
    Eigen::Vector3f ai;
    Eigen::Vector3f bkc;

    unsigned int* raysPerPixel;
    unsigned int raysPerPixelSize;

    unsigned int speedup;

    bool antialiasing;
    bool twosiderender;
    bool globalillum;
};

#endif