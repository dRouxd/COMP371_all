
#include "SphereGeom.h"

#include "util.hpp"

SphereGeom::SphereGeom(std::string comment, RGB ac, RGB dc, RGB sc,
                    float ka, float kd, float ks, float pc, Eigen::Vector3f centre, float radius):
                    Geometric(ObjectType::Sphere, comment, ac, dc, sc, ka, kd, ks, pc)
{
    this->centre = centre;
    this->radius = radius;
}

SphereGeom::SphereGeom(nlohmann::json j) : Geometric(j)
{
    this->centre = JsonArrayToVector3f(j["centre"]);
    this->radius = j["radius"].get<float>();
}

SphereGeom::SphereGeom(const SphereGeom& so) : Geometric(so)
{
    this->centre = Eigen::Vector3f(so.centre);
    this->radius = so.radius;
}

float SphereGeom::rayIntersect(Ray* ray)
{
    float dist = -1.0;

    Eigen::Vector3f L = this->centre - ray->getOrigin();
    float ld = L.dot(ray->getDirection());
    if(ld < 0)
        return dist;

    float lld = sqrt(L.dot(L) - ld * ld);
    if(lld >= this->radius)
        return dist;

    float rlld = sqrt(pow(this->radius, 2) - lld*lld);

    // Sphere intersection points
    float t0 = ld - rlld;
    float t1 = ld + rlld;

    // If sphere is ahead of camera
    if(t0 > 0 && t1 > 0)
        dist = t0;

    // If camera is in sphere
    else if(t0 < 0 && t1 > 0)
        dist = t1;

    return dist;

}

Eigen::Vector3f SphereGeom::getNormalFromPointOnSphere(Eigen::Vector3f p) const
{
    return CreateNormalFrom2Points(this->centre, p);
}

void SphereGeom::print()
{
    std::cout << "[SphereGeom"
        << " ac:" << this->ac
        << " dc:" << this->dc
        << " sc:" << this->sc
        << " ka:" << this->ka << " kd:" << this->kd << " ks:" << this->ks << " pc:" << this->pc
        << " center: " << PrintVector3fStrOneLine(this->centre) << " radius: " << this->radius
        << "]";
}