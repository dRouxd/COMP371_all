
#include "SphereObject.h"

#include "util.hpp"

SphereObject::SphereObject(ObjectType type, Eigen::Vector3f ac, Eigen::Vector3f dc, Eigen::Vector3f sc,
                    float ka, float kd, float ks, float pc, Eigen::Vector3f centre, float radius):
                    GeometricObject(type, ac, dc, sc, ka, kd, ks, pc)
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
        << " ac:" << PrintVector3fStrOneLine(this->ac)
        << " dc:" << PrintVector3fStrOneLine(this->dc)
        << " sc:" << PrintVector3fStrOneLine(this->sc)
        << " ka:" << this->ka << " kd:" << this->kd << " ks:" << this->ks << " pc:" << this->pc
        << " center: " << PrintVector3fStrOneLine(this->centre) << " radius: " << this->radius
        << "]";
}

/*SPHEREOBJECT_OSTREAM_OP
{
    os << "[SPHEREOBJECT"
        << " ac:" << PrintVector3fStrOneLine(ro.getAC())
        << " dc:" << PrintVector3fStrOneLine(ro.getDC())
        << " sc:" << PrintVector3fStrOneLine(ro.getSC())
        << " ka:" << ro.getKA() << " kd:" << ro.getKD() << " ks:" << ro.getKS() << " pc:" << ro.getPC()
        << " center: " << PrintVector3fStrOneLine(ro.getCentre()) << " radius: " << ro.getRadius()
        << "]";
}*/