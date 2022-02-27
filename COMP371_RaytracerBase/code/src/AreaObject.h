#ifndef AREAOBJECT_H
#define AREAOBJECT_H

#include "LightObject.h"
#include "Rectangle.h"

class AreaObject : public LightObject, public Rectangle
{
public:
    AreaObject(ObjectType type, RGB id, RGB is, 
                Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4);
    AreaObject(nlohmann::json j);
    AreaObject(const AreaObject& ao);
    ~AreaObject() = default;
    void print();
};

#endif