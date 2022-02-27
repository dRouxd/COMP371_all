
#include "RectangleGeom.h"

#include "util.hpp"

RectangleGeom::RectangleGeom(std::string comment, RGB ac, RGB dc, RGB sc,
                    float ka, float kd, float ks, float pc, 
                    Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4):
                    Geometric(ObjectType::Rectangle, comment, ac, dc, sc, ka, kd, ks, pc),
                    Rectangle(p1, p2, p3, p4)
{
}

RectangleGeom::RectangleGeom(nlohmann::json j) : Geometric(j), Rectangle(j)
{
}

RectangleGeom::RectangleGeom(const RectangleGeom& ro) : Geometric(ro), Rectangle(ro)
{
}

void RectangleGeom::print()
{
    std::cout << "[RectangleGeom"
        << " ac:" << this->ac
        << " dc:" << this->dc
        << " sc:" << this->sc
        << " ka:" << this->ka << " kd:" << this->kd << " ks:" << this->ks << " pc:" << this->pc
        << " p1:" << PrintVector3fStrOneLine(this->p1)
        << " p2:" << PrintVector3fStrOneLine(this->p2)
        << " p3:" << PrintVector3fStrOneLine(this->p3)
        << " p4:" << PrintVector3fStrOneLine(this->p4)
        << " normal:" << PrintVector3fStrOneLine(this->normal)
        << "]";
}