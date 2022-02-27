#ifndef POINTOBJECT_H
#define POINTOBJECT_H

#include "LightObject.h"

class PointObject : public LightObject
{
public:
    PointObject(ObjectType type, RGB id, RGB is, Eigen::Vector3f centre);
    PointObject(nlohmann::json j);
    PointObject(const PointObject& po);
    ~PointObject() = default;
    void print();

    inline Eigen::Vector3f getCentre() const { return centre; };

private:
    Eigen::Vector3f centre;

};

#endif