#ifndef UTIL_HPP
#define UTIL_HPP

#include "Geometric.h"
#include "Light.h"
#include "Ray.h"
#include "Camera.h"
#include "RGB.h"

#include "json.hpp"

#include <string>

#include <Eigen/Core>

const char* ObjectTypeToString(ObjectType type);

ObjectType StringToObjectType(std::string type);

Eigen::Vector3f JsonArrayToVector3f(nlohmann::json j);

RGB JsonArrayToRGB(nlohmann::json j);

Geometric* CreateGeometricObjectFromJson(nlohmann::json j);

Light* CreateLightObjectFromJson(nlohmann::json j);

Ray* CreateRayFromCamera(Camera* camera, int x, int y);

Ray* CreateRayFromPoints(Eigen::Vector3f p1, Eigen::Vector3f p2);

Eigen::Vector3f CreateNormalFrom2Points(Eigen::Vector3f p1, Eigen::Vector3f p2);

std::string PrintMatrixXfStrOneLine(const Eigen::MatrixXf& m);

std::string PrintVector3fStrOneLine(const Eigen::Vector3f& v);

float GetDistanceBetween2Points(Eigen::Vector3f p1, Eigen::Vector3f p2);

#endif