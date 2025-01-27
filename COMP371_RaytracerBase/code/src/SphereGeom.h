#ifndef SPHEREOBJECT_H
#define SPHEREOBJECT_H

#include "Geometric.h"
#include "Ray.h"

class SphereGeom : public Geometric
{
public:
    SphereGeom(std::string comment, RGB ac, RGB dc, RGB sc,
                    float ka, float kd, float ks, float pc, Eigen::Vector3f centre, float radius);
    SphereGeom(nlohmann::json j);
    SphereGeom(const SphereGeom& so);
    ~SphereGeom() = default;
    void print();

    float rayIntersect(Ray* ray);

    inline Eigen::Vector3f getCentre() const { return centre; };
    inline float getRadius() const { return radius; };

    Eigen::Vector3f getNormalFromPointOnSphere(Eigen::Vector3f p) const;

private:
    Eigen::Vector3f centre;
    float radius;
};

#endif