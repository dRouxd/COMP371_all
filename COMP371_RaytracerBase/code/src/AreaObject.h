#ifndef AREAOBJECT_H
#define AREAOBJECT_H

#include "LightObject.h"

#define AREAOBJECT_OSTREAM_OP std::ostream& operator<<(std::ostream& os, const AreaObject ao)

class AreaObject : public LightObject
{
public:
    AreaObject(ObjectType type, Eigen::Vector3f id, Eigen::Vector3f is, 
                Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3, Eigen::Vector3f p4);
    AreaObject(nlohmann::json j);
    AreaObject(const AreaObject& ao);
    ~AreaObject();

    inline Eigen::Vector3f getP1() const { return p1; };
    inline Eigen::Vector3f getP2() const { return p2; };
    inline Eigen::Vector3f getP3() const { return p3; };
    inline Eigen::Vector3f getP4() const { return p4; };

private:
    Eigen::Vector3f p1;
    Eigen::Vector3f p2;
    Eigen::Vector3f p3;
    Eigen::Vector3f p4;
};

AREAOBJECT_OSTREAM_OP;

#endif