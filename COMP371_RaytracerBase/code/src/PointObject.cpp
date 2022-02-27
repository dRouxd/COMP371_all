
#include "PointObject.h"

#include "util.hpp"

PointObject::PointObject(ObjectType type, RGB id, RGB is, Eigen::Vector3f centre) : LightObject(type, id, is)
{
    this->centre = centre;
}

PointObject::PointObject(nlohmann::json j) : LightObject(j)
{
    this->centre = JsonArrayToVector3f(j["centre"]);
}

PointObject::PointObject(const PointObject& po) : LightObject(po)
{
    this->centre = Eigen::Vector3f(po.centre);
}

void PointObject::print()
{
    std::cout << "[POINTOBJECT id:" << this->id
        << " is:" << this->is
        << " centre:" << PrintVector3fStrOneLine(this->centre)
        << "]";
}