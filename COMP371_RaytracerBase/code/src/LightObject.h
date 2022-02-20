#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#include "Object.h"

#include <Eigen/Core>

#include <iostream>

#define LIGHTOBJECT_OSTREAM_OP std::ostream& operator<<(std::ostream& os, const LightObject lo)

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

//LIGHTOBJECT_OSTREAM_OP;

#endif