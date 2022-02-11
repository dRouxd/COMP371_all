#ifndef OUTPUT_H
#define OUTPUT_H

#include "CameraObject.h"

#include "json.hpp"

#include <Eigen/Core>

class Output
{
public:
    Output(nlohmann::json j);
    ~Output();

    inline std::string getOutputFilename() const { return outputFilename; };
    inline CameraObject* getCamera() const { return camera; };
    inline Eigen::Vector3f getAI() const { return ai; };
    inline Eigen::Vector3f getBKC() const { return bkc; };

private:
    std::string outputFilename;
    CameraObject* camera;
    Eigen::Vector3f ai;
    Eigen::Vector3f bkc;
};

#endif