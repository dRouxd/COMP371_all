#ifndef GEOMETRICOBJECT_H
#define GEOMETRICOBJECT_H

#include "Object.h"

#include <Eigen/Core>

#include <iostream>
#include <string>

class GeometricObject : public Object
{
public:
    GeometricObject(ObjectType type, std::string comment, Eigen::Vector3f ac, Eigen::Vector3f dc, Eigen::Vector3f sc,
                    float ka, float kd, float ks, float pc);
    GeometricObject(nlohmann::json j);
    GeometricObject(const GeometricObject& go);
    virtual ~GeometricObject() = default;
    virtual void print() = 0;

    inline Eigen::Vector3f getAC() const { return ac; };
    inline Eigen::Vector3f getDC() const { return dc; };
    inline Eigen::Vector3f getSC() const { return sc; };

    inline float getKA() const { return ka; };
    inline float getKD() const { return kd; };
    inline float getKS() const { return ks; };

    inline float getPC() const { return pc; };

    std::string getComment() const { return comment; };

protected:
    Eigen::Vector3f ac;
    Eigen::Vector3f dc;
    Eigen::Vector3f sc;

    float ka;
    float kd;
    float ks;

    float pc;

    std::string comment;

};

#endif