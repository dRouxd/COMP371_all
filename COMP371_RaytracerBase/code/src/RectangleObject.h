#ifndef RECTANGLEOBJECT_H
#define RECTANGLEOBJECT_H

#include "GeometricObject.h"
#include "Rectangle.h"

class RectangleObject : public GeometricObject, public Rectangle
{
public:
    RectangleObject(std::string comment, RGB ac, RGB dc, RGB sc,
                    float ka, float kd, float ks, float pc, 
                    Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4);
    RectangleObject(nlohmann::json j);
    RectangleObject(const RectangleObject& ro);
    ~RectangleObject() = default;
    void print();
};

#endif