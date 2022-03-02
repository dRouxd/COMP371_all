#ifndef AREAOBJECT_H
#define AREAOBJECT_H

#include "Light.h"
#include "Rectangle.h"

class AreaLight : public Light, public Rectangle
{
public:
    AreaLight(ObjectType type, RGB id, RGB is, 
                Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4);
    AreaLight(nlohmann::json j);
    AreaLight(const AreaLight& ao);
    ~AreaLight() = default;

    Eigen::Vector3f generateRandomPoint() const;

    void print();
};

#endif