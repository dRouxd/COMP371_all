#ifndef UTIL_HPP
#define UTIL_HPP

#include "GeometricObject.h"
#include "LightObject.h"


#include "json.hpp"

#include <string>

#include <Eigen/Core>

const char* ObjectTypeToString(ObjectType type);

ObjectType StringToObjectType(std::string type);

Eigen::Vector3f JsonArrayToVector3f(nlohmann::json j);

GeometricObject* CreateGeometricObjectFromJson(nlohmann::json j);

LightObject* CreateLightObjectFromJson(nlohmann::json j);

const char* GetMatrixXfStrOneLine(Eigen::MatrixXf m);

const char* GetVector3fStrOneLine(Eigen::Vector3f v);



#endif