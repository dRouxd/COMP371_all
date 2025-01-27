#include "util.hpp"

#include "RectangleGeom.h"
#include "SphereGeom.h"
#include "PointLight.h"
#include "AreaLight.h"

#include <Eigen/Geometry>

#include <stdexcept>
#include <sstream>
#include <iostream>
#include <math.h>

const char* ObjectTypeToString(ObjectType type)
{
    switch(type)
    {
        case ObjectType::Sphere:
            return "sphere";
        case ObjectType::Rectangle:
            return "rectangle";
        case ObjectType::Point:
            return "point";
        case ObjectType::Area:
            return "area";
        default:
            throw std::runtime_error("Undefined object type enum");
    }
}

ObjectType StringToObjectType(std::string type)
{
    if(type == "sphere")
        return ObjectType::Sphere;
    else if(type == "rectangle")
        return ObjectType::Rectangle;
    else if(type == "point")
        return ObjectType::Point;
    else if(type == "area")
        return ObjectType::Area;
    throw std::runtime_error("Undefined object type string");
}

Eigen::Vector3f JsonArrayToVector3f(nlohmann::json j)
{
    if(j.size() != 3)
        throw std::runtime_error("JsonArrayToVector3f: Wrong number of json elements to convert to Vector3f");

    float elems[3];
    int i = 0;
    for(auto it = j.begin(); it != j.end(); ++it, ++i)
    {
        elems[i] = (*it).get<float>();
    }

    return Eigen::Vector3f(elems[0], elems[1], elems[2]);
}

RGB JsonArrayToRGB(nlohmann::json j)
{
    
    if(j.size() != 3)
        throw std::runtime_error("JsonArrayToVector3f: Wrong number of json elements to convert to Vector3f");

    float elems[3];
    int i = 0;
    for(auto it = j.begin(); it != j.end(); ++it, ++i)
    {
        elems[i] = (*it).get<float>();
    }

    return RGB(elems[0], elems[1], elems[2]);
}

Geometric* CreateGeometricObjectFromJson(nlohmann::json j)
{
    if(j.count("type") != 1)
        throw std::runtime_error("CreateGeometricObjectFromJson: Passed json does not contain type");

    ObjectType type = StringToObjectType(j["type"].get<std::string>());

    if(type != ObjectType::Rectangle && type != ObjectType::Sphere)
        throw std::runtime_error("CreateGeometricObjectFromJson: Passed json is not a geometric object");

    Geometric* go;

    if(type == ObjectType::Rectangle)
        go = new RectangleGeom(j);
    else if(type == ObjectType::Sphere)
        go = new SphereGeom(j);

    return go;
}

Light* CreateLightObjectFromJson(nlohmann::json j)
{
    if(j.count("type") != 1)
        throw std::runtime_error("CreateGeometricObjectFromJson: Passed json does not contain type");

    ObjectType type = StringToObjectType(j["type"].get<std::string>());

    if(type != ObjectType::Point && type != ObjectType::Area)
        throw std::runtime_error("CreateGeometricObjectFromJson: Passed json is not a geometric object");

    Light* lo;
    
    if(type == ObjectType::Point)
        lo = new PointLight(j);
    else if(type == ObjectType::Area)
        lo = new AreaLight(j);

    return lo;
}

Ray* CreateRayFromCamera(Camera* cam, int x, int y)
{
    float tanFov = tan((cam->getFov() / 2) * M_PI / 180);
    float pixSize = (2 * tanFov) / cam->getHeight();
    float halfPixSize = pixSize / 2;

    Eigen::Vector3f A = cam->getCentre() + cam->getLookat();
    Eigen::Vector3f B = A + (tanFov * cam->getUp());
    Eigen::Vector3f C = B - ( (cam->getWidth() / 2) * pixSize * cam->getRight() );

    Eigen::Vector3f pixelCenter = C + ((x * pixSize + halfPixSize) * cam->getRight()) - ((y * pixSize + halfPixSize) * cam->getUp());
    Eigen::Vector3f direction = (pixelCenter - cam->getCentre()) / (pixelCenter - cam->getCentre()).norm();

    Ray* ray = new Ray(cam->getCentre(), direction);

    return ray;
}

Ray* CreateRayFromPoints(Eigen::Vector3f p1, Eigen::Vector3f p2)
{
    Eigen::Vector3f direction = (p2 - p1) / (p2 - p1).norm();
    return new Ray(Eigen::Vector3f(p1), direction);
}

Eigen::Vector3f CreateNormalFrom2Points(Eigen::Vector3f p1, Eigen::Vector3f p2)
{
    return (p2 - p1) / (p2 - p1).norm();
}

std::string GetMatrixXfStrOneLine(const Eigen::MatrixXf& m)
{
    std::stringstream ss;

    if(m.cols() > 1)
        ss << "[";
    
    for(int j = 0; j < m.cols(); ++j)
    {
        ss << "[";
        for(int i = 0; i < m.rows(); ++i)
        {
            ss << m(i, j) ;
            if(i+1 != m.rows())
                ss << ", ";
        }
        ss << "]";
        
        if(j+1 != m.cols())
            ss << ", ";
    }
    
    if(m.cols() > 1)
        ss << "]";

    return ss.str();
}

std::string PrintVector3fStrOneLine(const Eigen::Vector3f& v)
{
    return GetMatrixXfStrOneLine(static_cast<Eigen::MatrixXf>(v));
}

float GetDistanceBetween2Points(Eigen::Vector3f p1, Eigen::Vector3f p2)
{
    return std::sqrt(std::pow(p2(0) - p1(0), 2) + std::pow(p2(1) - p1(1), 2) + std::pow(p2(2) - p1(2), 2));
}