#ifndef POINTOBJECT_H
#define POINTOBJECT_H

#include "LightObject.h"

#define POINTOBJECT_OSTREAM_OP std::ostream& operator<<(std::ostream& os, const PointObject po)

class PointObject : public LightObject
{
public:
    PointObject(ObjectType type, Eigen::Vector3f id, Eigen::Vector3f is, Eigen::Vector3f centre);
    PointObject(nlohmann::json j);
    PointObject(const PointObject& po);
    ~PointObject() = default;
    void print();

    inline Eigen::Vector3f getCentre() const { return centre; };

private:
    Eigen::Vector3f centre;

};

//POINTOBJECT_OSTREAM_OP;

#endif