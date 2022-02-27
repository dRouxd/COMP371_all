
#include "GeometricObject.h"

#include "util.hpp"

GeometricObject::GeometricObject(ObjectType type, std::string comment, RGB ac, RGB dc, RGB sc,
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

    this->comment = comment;
}

GeometricObject::GeometricObject(nlohmann::json j) : Object(j)
{

    this->ac = JsonArrayToRGB(j["ac"]);
    this->dc = JsonArrayToRGB(j["dc"]);
    this->sc = JsonArrayToRGB(j["sc"]);

    this->ka = j["ka"].get<float>();
    this->kd = j["kd"].get<float>();
    this->ks = j["ks"].get<float>();

    this->pc = j["pc"].get<float>();

    
    this->comment = j.contains(std::string("comment")) ? j["comment"].get<std::string>() : std::string("");
}

GeometricObject::GeometricObject(const GeometricObject& go) : Object(go)
{
    this->ac = RGB(go.ac);
    this->dc = RGB(go.dc);
    this->sc = RGB(go.sc);
    
    this->ka = go.ka;
    this->kd = go.kd;
    this->ks = go.ks;
    
    this->pc = go.pc;

    this->comment = go.comment;
}