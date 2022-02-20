
#include "GeometricObject.h"

#include "util.hpp"

GeometricObject::GeometricObject(ObjectType type, Eigen::Vector3f ac, Eigen::Vector3f dc, Eigen::Vector3f sc,
                                float ka, float kd, float ks,
                                float pc) : Object(type)
{

    this->ac = ac;
    this->dc = dc;
    this->sc = sc;

    this->ka = ka;
    this->kd = kd;
    this->ks = ks;

    this->pc = pc;
}

GeometricObject::GeometricObject(nlohmann::json j) : Object(j)
{

    this->ac = JsonArrayToVector3f(j["ac"]);
    this->dc = JsonArrayToVector3f(j["dc"]);
    this->sc = JsonArrayToVector3f(j["sc"]);

    this->ka = j["ka"].get<float>();
    this->kd = j["kd"].get<float>();
    this->ks = j["ks"].get<float>();

    this->pc = j["pc"].get<float>();
}

GeometricObject::GeometricObject(const GeometricObject& go) : Object(go)
{
    this->ac = Eigen::Vector3f(go.ac);
    this->dc = Eigen::Vector3f(go.dc);
    this->sc = Eigen::Vector3f(go.sc);
    
    this->ka = go.ka;
    this->kd = go.kd;
    this->ks = go.ks;
    
    this->pc = go.pc;
}

/*GEOMETRICOBJECT_OSTREAM_OP
{
    os << "[GEOMETRICOBJECT type:" << ObjectTypeToString(go.getType())
        << " ac:" << GetVector3fStrOneLine(go.getAC())
        << " dc:" << GetVector3fStrOneLine(go.getDC())
        << " sc:" << GetVector3fStrOneLine(go.getSC())
        << " ka:" << go.getKA() << " kd:" << go.getKD() << " ks:" << go.getKS() << " pc:" << go.getPC()
        << "]";
}*/