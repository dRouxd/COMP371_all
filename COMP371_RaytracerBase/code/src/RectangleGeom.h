#ifndef RECTANGLEOBJECT_H
#define RECTANGLEOBJECT_H

#include "Geometric.h"
#include "Rectangle.h"

class RectangleGeom : public Geometric, public Rectangle
{
public:
    RectangleGeom(std::string comment, RGB ac, RGB dc, RGB sc,
                    float ka, float kd, float ks, float pc, 
                    Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4);
    RectangleGeom(nlohmann::json j);
    RectangleGeom(const RectangleGeom& ro);
    ~RectangleGeom() = default;
    void print();
};

#endif