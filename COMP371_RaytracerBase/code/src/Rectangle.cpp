
#include "Rectangle.h"

#include "util.hpp"

#include <Eigen/Geometry>

Rectangle::Rectangle(Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
    calcNormal();
}

Rectangle::Rectangle(nlohmann::json j)
{
    this->p1 = JsonArrayToVector3f(j["p1"]);
    this->p2 = JsonArrayToVector3f(j["p2"]);
    this->p3 = JsonArrayToVector3f(j["p3"]);
    this->p4 = JsonArrayToVector3f(j["p4"]);
    calcNormal();
}

Rectangle::Rectangle(const Rectangle& r)
{
    
    this->p1 = Eigen::Vector3f(r.p1);
    this->p2 = Eigen::Vector3f(r.p2);
    this->p3 = Eigen::Vector3f(r.p3);
    this->p4 = Eigen::Vector3f(r.p4);
    calcNormal();
}

void Rectangle::calcNormal()
{
    this->normal = (p2 - p1).cross(p3 - p1).normalized();
}