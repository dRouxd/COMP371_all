#ifndef GEOMETRICOBJECT_H
#define GEOMETRICOBJECT_H

#include "Object.h"

#include <Eigen/Core>

#include <iostream>

#define GEOMETRICOBJECT_OSTREAM_OP std::ostream& operator<<(std::ostream& os, const GeometricObject go)

class GeometricObject : public Object
{
public:
    GeometricObject(ObjectType type, Eigen::Vector3f ac, Eigen::Vector3f dc, Eigen::Vector3f sc,
                    float ka, float kd, float ks, float pc);
    GeometricObject(nlohmann::json j);
    GeometricObject(const GeometricObject& go);
    virtual ~GeometricObject() = default;

    inline Eigen::Vector3f getAC() const { return ac; };
    inline Eigen::Vector3f getDC() const { return dc; };
    inline Eigen::Vector3f getSC() const { return sc; };

    inline float getKA() const { return ka; };
    inline float getKD() const { return kd; };
    inline float getKS() const { return ks; };

    inline float getPC() const { return pc; };

private:
    Eigen::Vector3f ac;
    Eigen::Vector3f dc;
    Eigen::Vector3f sc;

    float ka;
    float kd;
    float ks;

    float pc;

};

GEOMETRICOBJECT_OSTREAM_OP;

#endif