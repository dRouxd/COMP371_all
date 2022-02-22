
#include "Camera.h"

#include "util.hpp"

#include <Eigen/Geometry>

Camera::Camera(unsigned int w, unsigned int h, float fov, Eigen::Vector3f centre, Eigen::Vector3f up, Eigen::Vector3f lookat)
{
    this->w = w;
    this->h = h;
    this->fov = fov;
    this->centre = centre;
    this->up = up;
    this->lookat = lookat;
    calcRight();
}

Camera::Camera(nlohmann::json j)
{
    this->w = j["size"][0].get<unsigned int>();
    this->h = j["size"][1].get<unsigned int>();
    this->fov = j["fov"].get<float>();

    this->centre = JsonArrayToVector3f(j["centre"]);
    this->up = JsonArrayToVector3f(j["up"]);
    this->lookat = JsonArrayToVector3f(j["lookat"]);
    calcRight();
}

Camera::Camera(const Camera& co)
{
    this->w = co.w;
    this->h = co.h;
    this->fov = co.fov;

    this->centre = Eigen::Vector3f(co.centre);
    this->up = Eigen::Vector3f(co.up);
    this->lookat = Eigen::Vector3f(co.lookat);
    calcRight();
}

Camera::~Camera()
{

}

void Camera::calcRight() const
{
    this->right = this->lookat.cross(this->up);
}

CAMERAOBJECT_OSTREAM_OP
{
    os << "[CAMERAOBJECT"
        << " w:" << co.getWidth()
        << " h:" << co.getHeight()
        << " centre:" << PrintVector3fStrOneLine(co.getCentre())
        << " up:" << PrintVector3fStrOneLine(co.getUp())
        << " lookat:" << PrintVector3fStrOneLine(co.getLookat())
        << " right:" << PrintVector3fStrOneLine(co.getLookat())
        << "]";
}