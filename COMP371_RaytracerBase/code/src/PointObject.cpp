
#include "PointObject.h"

#include "util.hpp"

PointObject::PointObject(ObjectType type, Eigen::Vector3f id, Eigen::Vector3f is, Eigen::Vector3f centre) : LightObject(type, id, is)
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
    std::cout << "[POINTOBJECT id:" << PrintVector3fStrOneLine(this->id)
        << " is:" << PrintVector3fStrOneLine(this->is)
        << " centre:" << PrintVector3fStrOneLine(this->centre)
        << "]";
}

/*POINTOBJECT_OSTREAM_OP
{
    os << "[POINTOBJECT type:" << ObjectTypeToString(po.getType())
        << " id:" << PrintVector3fStrOneLine(po.getID())
        << " is:" << PrintVector3fStrOneLine(po.getIS())
        << " centre:" << PrintVector3fStrOneLine(po.getCentre())
        << "]";
}*/