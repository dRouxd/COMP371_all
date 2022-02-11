
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

PointObject::~PointObject()
{

}

POINTOBJECT_OSTREAM_OP
{
    os << "[POINTOBJECT type:" << ObjectTypeToString(po.getType())
        << " id:" << GetVector3fStrOneLine(po.getID())
        << " is:" << GetVector3fStrOneLine(po.getIS())
        << " centre:" << GetVector3fStrOneLine(po.getCentre())
        << "]";
}