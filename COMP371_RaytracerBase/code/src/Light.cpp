
#include "Light.h"

#include "util.hpp"

Light::Light(ObjectType type, RGB id, RGB is) : Object(type)
{
    this->id = id;
    this->is = is;
}

Light::Light(nlohmann::json j) : Object(j)
{
    this->id = JsonArrayToRGB(j["id"]);
    this->is = JsonArrayToRGB(j["is"]);
}

Light::Light(const Light& lo) : Object(lo)
{
    this->id = RGB(lo.id);
    this->is = RGB(lo.is);
}

RGB Light::getLightColor() const
{
    return this->id * this->is;
}