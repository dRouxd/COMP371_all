#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#include "Object.h"

#include <Eigen/Core>

#include <iostream>

class LightObject : public Object
{
public:
    LightObject(ObjectType type, Eigen::Vector3f id, Eigen::Vector3f is);
    LightObject(nlohmann::json j);
    LightObject(const LightObject& lo);
    virtual ~LightObject() = default;
    virtual void print() = 0;

    inline Eigen::Vector3f getID() const { return id; };
    inline Eigen::Vector3f getIS() const { return is; };

protected:
    Eigen::Vector3f id;
    Eigen::Vector3f is;

};

#endif