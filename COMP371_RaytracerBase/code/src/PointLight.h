#ifndef POINTOBJECT_H
#define POINTOBJECT_H

#include "Light.h"

class PointLight : public Light
{
public:
    PointLight(ObjectType type, RGB id, RGB is, Eigen::Vector3f centre);
    PointLight(nlohmann::json j);
    PointLight(const PointLight& po);
    ~PointLight() = default;
    void print();

    inline Eigen::Vector3f getCentre() const { return centre; };

private:
    Eigen::Vector3f centre;

};

#endif