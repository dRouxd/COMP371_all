#ifndef SPHEREOBJECT_H
#define SPHEREOBJECT_H

#include "GeometricObject.h"

class SphereObject : public GeometricObject
{
public:
    SphereObject(std::string comment, Eigen::Vector3f ac, Eigen::Vector3f dc, Eigen::Vector3f sc,
                    float ka, float kd, float ks, float pc, Eigen::Vector3f centre, float radius);
    SphereObject(nlohmann::json j);
    SphereObject(const SphereObject& so);
    ~SphereObject() = default;
    void print();

    inline Eigen::Vector3f getCentre() const { return centre; };
    inline float getRadius() const { return radius; };

    Eigen::Vector3f getNormalFromPointOnSphere(Eigen::Vector3f point) const;

private:
    Eigen::Vector3f centre;
    float radius;
};

#endif