
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

Eigen::Vector3f SphereGeom::getNormalFromPointOnSphere(Eigen::Vector3f point) const
{
    // TODO: Calculate the normal using the center of the sphere and the given point
    return Eigen::Vector3f(1.0, 1.0, 1.0);
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