
#include "LightObject.h"

#include "util.hpp"

LightObject::LightObject(ObjectType type, RGB id, RGB is) : Object(type)
{
    this->id = id;
    this->is = is;
}

LightObject::LightObject(nlohmann::json j) : Object(j)
{
    this->id = JsonArrayToRGB(j["id"]);
    this->is = JsonArrayToRGB(j["is"]);
}

LightObject::LightObject(const LightObject& lo) : Object(lo)
{
    this->id = RGB(lo.id);
    this->is = RGB(lo.is);
}