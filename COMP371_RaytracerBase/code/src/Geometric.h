#ifndef GEOMETRICOBJECT_H
#define GEOMETRICOBJECT_H

#include "Object.h"
#include "RGB.h"

#include <Eigen/Core>

#include <iostream>
#include <string>

class RGB;

class Geometric : public Object
{
public:
    Geometric(ObjectType type, std::string comment, RGB ac, RGB dc, RGB sc,
                    float ka, float kd, float ks, float pc);
    Geometric(nlohmann::json j);
    Geometric(const Geometric& go);
    virtual ~Geometric() = default;
    virtual void print() = 0;

    inline RGB getAC() const { return ac; };
    inline RGB getDC() const { return dc; };
    inline RGB getSC() const { return sc; };

    inline float getKA() const { return ka; };
    inline float getKD() const { return kd; };
    inline float getKS() const { return ks; };

    inline float getPC() const { return pc; };

    std::string getComment() const { return comment; };

    inline RGB getAmbiantColor() const { return ac * ka; };
    inline RGB getDiffuseColor() const { return dc * kd; };
    inline RGB getSpecularColor() const { return sc * ks; };

protected:
    RGB ac;
    RGB dc;
    RGB sc;

    float ka;
    float kd;
    float ks;

    float pc;

    std::string comment;

};

#endif