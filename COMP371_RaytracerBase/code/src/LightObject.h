#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#include "Object.h"
#include "RGB.h"

#include <Eigen/Core>

#include <iostream>

class RGB;

class LightObject : public Object
{
public:
    LightObject(ObjectType type, RGB id, RGB is);
    LightObject(nlohmann::json j);
    LightObject(const LightObject& lo);
    virtual ~LightObject() = default;
    virtual void print() = 0;

    inline RGB getID() const { return id; };
    inline RGB getIS() const { return is; };

protected:
    RGB id;
    RGB is;

};

#endif