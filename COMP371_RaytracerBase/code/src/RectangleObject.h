#ifndef RECTANGLEOBJECT_H
#define RECTANGLEOBJECT_H

#include "GeometricObject.h"

#define RECTANGLEOBJECT_OSTREAM_OP std::ostream& operator<<(std::ostream& os, const RectangleObject ro)

class RectangleObject : public GeometricObject
{
public:
    RectangleObject(ObjectType type, Eigen::Vector3f ac, Eigen::Vector3f dc, Eigen::Vector3f sc,
                    float ka, float kd, float ks, float pc, 
                    Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4);
    RectangleObject(nlohmann::json j);
    RectangleObject(const RectangleObject& ro);
    ~RectangleObject() = default;
    void print();

    inline Eigen::Vector3f getP1() const { return p1; };
    inline Eigen::Vector3f getP2() const { return p2; };
    inline Eigen::Vector3f getP3() const { return p3; };
    inline Eigen::Vector3f getP4() const { return p4; };
    inline Eigen::Vector3f getNormal() const { return normal; };

private:

    void calcNormal();

    Eigen::Vector3f p1;
    Eigen::Vector3f p2;
    Eigen::Vector3f p3;
    Eigen::Vector3f p4;
    Eigen::Vector3f normal;
};

//RECTANGLEOBJECT_OSTREAM_OP;

#endif