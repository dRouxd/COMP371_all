
#include "AreaLight.h"

#include "util.hpp"

#include <random>

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

Eigen::Vector3f AreaLight::generateRandomPoint() const
{
    Eigen::Vector3f p1p2 = this->p2 - this->p1;
    Eigen::Vector3f p1p4 = this->p4 - this->p1;
    
    std::random_device rd; 
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    float randx = dist(eng);
    float randy = dist(eng);

    return this->p1 + p1p2 * randx + p1p4 * randy;
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