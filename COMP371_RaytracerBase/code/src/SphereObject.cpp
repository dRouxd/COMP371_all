
#include "SphereObject.h"

#include "util.hpp"

SphereObject::SphereObject(std::string comment, RGB ac, RGB dc, RGB sc,
                    float ka, float kd, float ks, float pc, Eigen::Vector3f centre, float radius):
                    GeometricObject(ObjectType::Sphere, comment, ac, dc, sc, ka, kd, ks, pc)
{
    this->centre = centre;
    this->radius = radius;
}

SphereObject::SphereObject(nlohmann::json j) : GeometricObject(j)
{
    this->centre = JsonArrayToVector3f(j["centre"]);
    this->radius = j["radius"].get<float>();
}

SphereObject::SphereObject(const SphereObject& so) : GeometricObject(so)
{
    this->centre = Eigen::Vector3f(so.centre);
    this->radius = so.radius;
}

Eigen::Vector3f SphereObject::getNormalFromPointOnSphere(Eigen::Vector3f point) const
{
    // TODO: Calculate the normal using the center of the sphere and the given point
    return Eigen::Vector3f(1.0, 1.0, 1.0);
}

void SphereObject::print()
{
    std::cout << "[SPHEREOBJECT"
        << " ac:" << this->ac
        << " dc:" << this->dc
        << " sc:" << this->sc
        << " ka:" << this->ka << " kd:" << this->kd << " ks:" << this->ks << " pc:" << this->pc
        << " center: " << PrintVector3fStrOneLine(this->centre) << " radius: " << this->radius
        << "]";
}