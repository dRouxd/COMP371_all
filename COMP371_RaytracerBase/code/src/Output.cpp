
#include "Output.h"

#include "util.hpp"

Output::Output(nlohmann::json j)
{
    this->camera = new CameraObject(j);
    this->outputFilename = std::string(j["filename"].get<std::string>());
    
    this->ai = JsonArrayToVector3f(j["ai"]);
    this->bkc = JsonArrayToVector3f(j["bkc"]);
}

Output::~Output()
{

}