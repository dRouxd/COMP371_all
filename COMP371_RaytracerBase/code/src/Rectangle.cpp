
#include "Rectangle.h"

#include "util.hpp"

#include <Eigen/Geometry>

#include <cmath>

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


float Rectangle::rayIntersect(Ray* ray)
{
    float dist = -1.0;

    float a = this->normal.dot(ray->getDirection());

    // Is the ray and the plane parallel?
    if (std::fpclassify(fabs(a)) == FP_ZERO)
        return dist;

    float t = this->normal.dot(this->p1 - ray->getOrigin()) / a;

    // Is the plane behind the ray?
    if(t < 0)
        return dist;

    Eigen::Vector3f p = ray->getOrigin() + t * ray->getDirection();

    // Is the point inside the rectangle?
    Eigen::Vector3f e1 = this->p2 - this->p1;
    Eigen::Vector3f e2 = this->p3 - this->p2;
    Eigen::Vector3f e3 = this->p4 - this->p3;
    Eigen::Vector3f e4 = this->p1 - this->p4;

    Eigen::Vector3f c1 = p - this->p1;
    Eigen::Vector3f c2 = p - this->p2;
    Eigen::Vector3f c3 = p - this->p3;
    Eigen::Vector3f c4 = p - this->p4;

    if( this->normal.dot(e1.cross(c1)) > 0 &&
        this->normal.dot(e2.cross(c2)) > 0 &&
        this->normal.dot(e3.cross(c3)) > 0 &&
        this->normal.dot(e4.cross(c4)) > 0)
        dist = t;

    return dist;
}

void Rectangle::calcNormal()
{
    this->normal = (p2 - p1).cross(p3 - p1).normalized();
}