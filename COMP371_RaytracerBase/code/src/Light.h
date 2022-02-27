#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#include "Object.h"
#include "RGB.h"

#include <Eigen/Core>

#include <iostream>

class RGB;

class Light : public Object
{
public:
    Light(ObjectType type, RGB id, RGB is);
    Light(nlohmann::json j);
    Light(const Light& lo);
    virtual ~Light() = default;
    virtual void print() = 0;

    inline RGB getID() const { return id; };
    inline RGB getIS() const { return is; };
    
    inline RGB getLightColor() const { return this->id * this->is; };

protected:
    RGB id;
    RGB is;

};

#endif