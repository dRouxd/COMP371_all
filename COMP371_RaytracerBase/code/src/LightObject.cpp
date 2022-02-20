
#include "LightObject.h"

#include "util.hpp"

LightObject::LightObject(ObjectType type, Eigen::Vector3f id, Eigen::Vector3f is) : Object(type)
{
    this->id = id;
    this->is = is;
}

LightObject::LightObject(nlohmann::json j) : Object(j)
{
    this->id = JsonArrayToVector3f(j["id"]);
    this->is = JsonArrayToVector3f(j["is"]);
}

LightObject::LightObject(const LightObject& lo) : Object(lo)
{
    this->id = Eigen::Vector3f(lo.id);
    this->is = Eigen::Vector3f(lo.is);
}

/*LIGHTOBJECT_OSTREAM_OP
{
    os << "[LIGHTOBJECT type:" << ObjectTypeToString(lo.getType())
        << " id:" << GetVector3fStrOneLine(lo.getID())
        << " is:" << GetVector3fStrOneLine(lo.getIS())
        << "]";
}*/