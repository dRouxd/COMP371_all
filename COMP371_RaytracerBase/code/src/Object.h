#ifndef OBJECT_H
#define OBJECT_H

#include "json.hpp"

#include <string>
#include <iostream>

enum ObjectType{Sphere = 0, Rectangle = 1, Point = 2, Area = 3};

#define OBJECT_OSTREAM_OP std::ostream& operator<<(std::ostream& os, const Object* o)

class Object
{
public:
    Object(ObjectType type);
    Object(nlohmann::json j);
    Object(const Object& o);
    virtual ~Object() = default;
    virtual void print() = 0;

    inline ObjectType getType() const { return type; };

protected:
    ObjectType type;
};

//OBJECT_OSTREAM_OP;

#endif