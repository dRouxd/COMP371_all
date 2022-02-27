
#include "AreaObject.h"

#include "util.hpp"

AreaObject::AreaObject(ObjectType type, RGB id, RGB is, 
                Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4): 
                LightObject(type, id, is), Rectangle(p1, p2, p3, p4)
{
}

AreaObject::AreaObject(nlohmann::json j) : LightObject(j), Rectangle(j)
{
}

AreaObject::AreaObject(const AreaObject& ao) : LightObject(ao), Rectangle(ao)
{
}

void AreaObject::print()
{
    std::cout << "[AREAOBJECT"
        << " id:" << this->id
        << " is:" << this->is
        << " p1:" << PrintVector3fStrOneLine(this->p1)
        << " p2:" << PrintVector3fStrOneLine(this->p2)
        << " p3:" << PrintVector3fStrOneLine(this->p3)
        << " p4:" << PrintVector3fStrOneLine(this->p4)
        << "]";
}