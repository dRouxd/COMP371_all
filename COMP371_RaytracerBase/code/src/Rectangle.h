#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "json.hpp"

#include <Eigen/Core>

class Rectangle
{
public:
    Rectangle(Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4);
    Rectangle(nlohmann::json j);
    Rectangle(const Rectangle& r);
    ~Rectangle() = default;

    inline Eigen::Vector3f getP1() const { return p1; };
    inline Eigen::Vector3f getP2() const { return p2; };
    inline Eigen::Vector3f getP3() const { return p3; };
    inline Eigen::Vector3f getP4() const { return p4; };
    inline Eigen::Vector3f getNormal() const { return normal; };

protected:

    void calcNormal();

    Eigen::Vector3f p1;
    Eigen::Vector3f p2;
    Eigen::Vector3f p3;
    Eigen::Vector3f p4;
    Eigen::Vector3f normal;
};

#endif