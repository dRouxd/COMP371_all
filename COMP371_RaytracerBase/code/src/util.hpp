#ifndef UTIL_HPP
#define UTIL_HPP

#include "GeometricObject.h"
#include "LightObject.h"
#include "Ray.h"
#include "Camera.h"

#include "json.hpp"

#include <string>

#include <Eigen/Core>

const char* ObjectTypeToString(ObjectType type);

ObjectType StringToObjectType(std::string type);

Eigen::Vector3f JsonArrayToVector3f(nlohmann::json j);

GeometricObject* CreateGeometricObjectFromJson(nlohmann::json j);

LightObject* CreateLightObjectFromJson(nlohmann::json j);

Ray* CreateRayFromCamera(Camera* camera, int x, int y);

Ray* CreateRayFromPoints(Eigen::Vector3f p1, Eigen::Vector3f p2);

Eigen::Vector3f CreateNormalFrom2Points(Eigen::Vector3f p1, Eigen::Vector3f p2);

std::string PrintMatrixXfStrOneLine(const Eigen::MatrixXf& m);

std::string PrintVector3fStrOneLine(const Eigen::Vector3f& v);



#endif