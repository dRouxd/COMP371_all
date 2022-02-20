
#include "RectangleObject.h"

#include "util.hpp"

RectangleObject::RectangleObject(ObjectType type, Eigen::Vector3f ac, Eigen::Vector3f dc, Eigen::Vector3f sc,
                    float ka, float kd, float ks, float pc, 
                    Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4):
                    GeometricObject(type, ac, dc, sc, ka, kd, ks, pc)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
}

RectangleObject::RectangleObject(nlohmann::json j) : GeometricObject(j)
{
    this->p1 = JsonArrayToVector3f(j["p1"]);
    this->p2 = JsonArrayToVector3f(j["p2"]);
    this->p3 = JsonArrayToVector3f(j["p3"]);
    this->p4 = JsonArrayToVector3f(j["p4"]);
}

RectangleObject::RectangleObject(const RectangleObject& ro) : GeometricObject(ro)
{
    this->p1 = Eigen::Vector3f(ro.p1);
    this->p2 = Eigen::Vector3f(ro.p2);
    this->p3 = Eigen::Vector3f(ro.p3);
    this->p4 = Eigen::Vector3f(ro.p4);
}

void RectangleObject::print()
{
    std::cout << "[RECTANGLEOBJECT"
        << " ac:" << GetVector3fStrOneLine(this->ac)
        << " dc:" << GetVector3fStrOneLine(this->dc)
        << " sc:" << GetVector3fStrOneLine(this->sc)
        << " ka:" << this->ka << " kd:" << this->kd << " ks:" << this->ks << " pc:" << this->pc
        << " p1:" << GetVector3fStrOneLine(this->p1)
        << " p2:" << GetVector3fStrOneLine(this->p2)
        << " p3:" << GetVector3fStrOneLine(this->p3)
        << " p4:" << GetVector3fStrOneLine(this->p4)
        << "]";
}

/*RECTANGLEOBJECT_OSTREAM_OP
{
    os << "[RECTANGLEOBJECT"
        << " ac:" << GetVector3fStrOneLine(ro.getAC())
        << " dc:" << GetVector3fStrOneLine(ro.getDC())
        << " sc:" << GetVector3fStrOneLine(ro.getSC())
        << " ka:" << ro.getKA() << " kd:" << ro.getKD() << " ks:" << ro.getKS() << " pc:" << ro.getPC()
        << " p1:" << GetVector3fStrOneLine(ro.getP1())
        << " p2:" << GetVector3fStrOneLine(ro.getP2())
        << " p3:" << GetVector3fStrOneLine(ro.getP3())
        << " p4:" << GetVector3fStrOneLine(ro.getP4())
        << "]";
}*/