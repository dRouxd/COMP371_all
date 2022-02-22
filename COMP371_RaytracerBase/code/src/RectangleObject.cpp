
#include "RectangleObject.h"

#include "util.hpp"

#include <Eigen/Geometry>

RectangleObject::RectangleObject(ObjectType type, Eigen::Vector3f ac, Eigen::Vector3f dc, Eigen::Vector3f sc,
                    float ka, float kd, float ks, float pc, 
                    Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4):
                    GeometricObject(type, ac, dc, sc, ka, kd, ks, pc)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
    calcNormal();
}

RectangleObject::RectangleObject(nlohmann::json j) : GeometricObject(j)
{
    this->p1 = JsonArrayToVector3f(j["p1"]);
    this->p2 = JsonArrayToVector3f(j["p2"]);
    this->p3 = JsonArrayToVector3f(j["p3"]);
    this->p4 = JsonArrayToVector3f(j["p4"]);
    calcNormal();
}

RectangleObject::RectangleObject(const RectangleObject& ro) : GeometricObject(ro)
{
    this->p1 = Eigen::Vector3f(ro.p1);
    this->p2 = Eigen::Vector3f(ro.p2);
    this->p3 = Eigen::Vector3f(ro.p3);
    this->p4 = Eigen::Vector3f(ro.p4);
    calcNormal();
}

void RectangleObject::print()
{
    std::cout << "[RECTANGLEOBJECT"
        << " ac:" << PrintVector3fStrOneLine(this->ac)
        << " dc:" << PrintVector3fStrOneLine(this->dc)
        << " sc:" << PrintVector3fStrOneLine(this->sc)
        << " ka:" << this->ka << " kd:" << this->kd << " ks:" << this->ks << " pc:" << this->pc
        << " p1:" << PrintVector3fStrOneLine(this->p1)
        << " p2:" << PrintVector3fStrOneLine(this->p2)
        << " p3:" << PrintVector3fStrOneLine(this->p3)
        << " p4:" << PrintVector3fStrOneLine(this->p4)
        << " norma;:" << PrintVector3fStrOneLine(this->normal)
        << "]";
}

void RectangleObject::calcNormal()
{
    this->normal = (p2 - p1).cross(p3 - p1).normalized();
}

/*RECTANGLEOBJECT_OSTREAM_OP
{
    os << "[RECTANGLEOBJECT"
        << " ac:" << PrintVector3fStrOneLine(ro.getAC())
        << " dc:" << PrintVector3fStrOneLine(ro.getDC())
        << " sc:" << PrintVector3fStrOneLine(ro.getSC())
        << " ka:" << ro.getKA() << " kd:" << ro.getKD() << " ks:" << ro.getKS() << " pc:" << ro.getPC()
        << " p1:" << PrintVector3fStrOneLine(ro.getP1())
        << " p2:" << PrintVector3fStrOneLine(ro.getP2())
        << " p3:" << PrintVector3fStrOneLine(ro.getP3())
        << " p4:" << PrintVector3fStrOneLine(ro.getP4())
        << "]";
}*/