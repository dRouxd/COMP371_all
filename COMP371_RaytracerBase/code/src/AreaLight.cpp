
#include "AreaLight.h"

#include "util.hpp"

AreaLight::AreaLight(ObjectType type, RGB id, RGB is, 
                Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4): 
                Light(type, id, is), Rectangle(p1, p2, p3, p4)
{
}

AreaLight::AreaLight(nlohmann::json j) : Light(j), Rectangle(j)
{
}

AreaLight::AreaLight(const AreaLight& ao) : Light(ao), Rectangle(ao)
{
}

void AreaLight::print()
{
    std::cout << "[AreaLight"
        << " id:" << this->id
        << " is:" << this->is
        << " p1:" << PrintVector3fStrOneLine(this->p1)
        << " p2:" << PrintVector3fStrOneLine(this->p2)
        << " p3:" << PrintVector3fStrOneLine(this->p3)
        << " p4:" << PrintVector3fStrOneLine(this->p4)
        << "]";
}