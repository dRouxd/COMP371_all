
#include "Object.h"
#include "util.hpp"

#include <stdexcept>
#include <string>



Object::Object(ObjectType type)
{
    this->type = type;
}

Object::Object(nlohmann::json j)
{
    this->type = StringToObjectType(j["type"].get<std::string>());
}

Object::Object(const Object& o)
{
    this->type = o.type;
}

OBJECT_OSTREAM_OP
{
    os << "[Object type:" << ObjectTypeToString(o.getType()) << "]";
}