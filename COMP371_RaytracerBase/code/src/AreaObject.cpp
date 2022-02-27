
#include "AreaObject.h"

#include "util.hpp"

AreaObject::AreaObject(ObjectType type, RGB id, RGB is, 
                Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4): LightObject(type, id, is)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
}

AreaObject::AreaObject(nlohmann::json j) : LightObject(j)
{
    this->p1 = JsonArrayToVector3f(j["p1"]);
    this->p2 = JsonArrayToVector3f(j["p2"]);
    this->p3 = JsonArrayToVector3f(j["p3"]);
    this->p4 = JsonArrayToVector3f(j["p4"]);
}

AreaObject::AreaObject(const AreaObject& ao) : LightObject(ao)
{
    this->p1 = Eigen::Vector3f(ao.p1);
    this->p2 = Eigen::Vector3f(ao.p2);
    this->p3 = Eigen::Vector3f(ao.p3);
    this->p4 = Eigen::Vector3f(ao.p4);
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