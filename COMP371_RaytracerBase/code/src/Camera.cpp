
#include "Camera.h"

#include "util.hpp"


Camera::Camera(unsigned int w, unsigned int h, float fov, Eigen::Vector3f centre, Eigen::Vector3f up, Eigen::Vector3f lookat)
{
    this->w = w;
    this->h = h;
    this->fov = fov;
    this->centre = centre;
    this->up = up;
    this->lookat = lookat;
}

Camera::Camera(nlohmann::json j)
{
    this->w = j["size"][0].get<unsigned int>();
    this->h = j["size"][1].get<unsigned int>();
    this->fov = j["fov"].get<float>();

    this->centre = JsonArrayToVector3f(j["centre"]);
    this->up = JsonArrayToVector3f(j["up"]);
    this->lookat = JsonArrayToVector3f(j["lookat"]);
}

Camera::Camera(const Camera& co)
{
    this->w = co.w;
    this->h = co.h;
    this->fov = co.fov;

    this->centre = Eigen::Vector3f(co.centre);
    this->up = Eigen::Vector3f(co.up);
    this->lookat = Eigen::Vector3f(co.lookat);
}

Camera::~Camera()
{

}

CAMERAOBJECT_OSTREAM_OP
{
    os << "[CAMERAOBJECT"
        << " w:" << co.getWidth()
        << " h:" << co.getHeight()
        << " centre:" << GetVector3fStrOneLine(co.getCentre())
        << " up:" << GetVector3fStrOneLine(co.getUp())
        << " lookat:" << GetVector3fStrOneLine(co.getLookat())
        << "]";
}