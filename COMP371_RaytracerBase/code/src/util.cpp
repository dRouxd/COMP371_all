#include "util.hpp"

#include "RectangleObject.h"
#include "SphereObject.h"
#include "PointObject.h"
#include "AreaObject.h"

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

GeometricObject* CreateGeometricObjectFromJson(nlohmann::json j)
{
    if(j.count("type") != 1)
        throw std::runtime_error("CreateGeometricObjectFromJson: Passed json does not contain type");

    ObjectType type = StringToObjectType(j["type"].get<std::string>());

    if(type != Rectangle && type != Sphere)
        throw std::runtime_error("CreateGeometricObjectFromJson: Passed json is not a geometric object");

    GeometricObject* go;

    if(type == Rectangle)
        go = new RectangleObject(j);
    else if(type == Sphere)
        go = new SphereObject(j);

    return go;
}

LightObject* CreateLightObjectFromJson(nlohmann::json j)
{
    if(j.count("type") != 1)
        throw std::runtime_error("CreateGeometricObjectFromJson: Passed json does not contain type");

    ObjectType type = StringToObjectType(j["type"].get<std::string>());

    if(type != Point && type != Area)
        throw std::runtime_error("CreateGeometricObjectFromJson: Passed json is not a geometric object");

    LightObject* lo;
    
    if(type == Point)
        lo = new PointObject(j);
    else if(type == Area)
        lo = new AreaObject(j);

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