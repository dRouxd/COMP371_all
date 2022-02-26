
#include "Ray.h"

#include "util.hpp"
#include "RGB.h"

#include <iostream>

Ray::Ray(Eigen::Vector3f origin, Eigen::Vector3f direction, Eigen::Vector3f color)
{
    this->origin = Eigen::Vector3f(origin);
    this->direction = Eigen::Vector3f(direction);
    this->color = Eigen::Vector3f(color);
}

Ray::Ray(const Ray& r)
{
    this->origin = r.origin;
    this->direction = r.direction;
    this->color = r.color;
}

void Ray::print()
{
    std::cout << "[RAY origin:" << PrintVector3fStrOneLine(this->origin)
                << " direction:" << PrintVector3fStrOneLine(this->direction)
                << " color:" << PrintVector3fStrOneLine(this->color) 
                << "]";
}

void Ray::setColor(const Eigen::Vector3f& color)
{
    this->color = Eigen::Vector3f(color);
}

void Ray::setColor(const RGB& color)
{
    Eigen::Vector3f c(color(0), color(1), color(2));
    this->color = c;
}