
#include "PointLight.h"

#include "util.hpp"

PointLight::PointLight(ObjectType type, RGB id, RGB is, Eigen::Vector3f centre) : Light(type, id, is)
{
    this->centre = centre;
}

PointLight::PointLight(nlohmann::json j) : Light(j)
{
    this->centre = JsonArrayToVector3f(j["centre"]);
}

PointLight::PointLight(const PointLight& po) : Light(po)
{
    this->centre = Eigen::Vector3f(po.centre);
}

void PointLight::print()
{
    std::cout << "[PointLight id:" << this->id
        << " is:" << this->is
        << " centre:" << PrintVector3fStrOneLine(this->centre)
        << "]";
}