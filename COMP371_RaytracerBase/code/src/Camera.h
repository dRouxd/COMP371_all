#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Core>

#include "json.hpp"

#define CAMERAOBJECT_OSTREAM_OP std::ostream& operator<<(std::ostream& os, const Camera co)

class Camera
{
public:
    Camera(unsigned int w, unsigned int h, float fov, Eigen::Vector3f centre, Eigen::Vector3f up, Eigen::Vector3f lookat);
    Camera(nlohmann::json j);
    Camera(const Camera& co);
    ~Camera();

    inline unsigned int getWidth() const { return w; }
    inline unsigned int getHeight() const { return h; }
    inline float getFov() const { return fov; };
    inline Eigen::Vector3f getCentre() const { return centre; };
    inline Eigen::Vector3f getUp() const { return up; };
    inline Eigen::Vector3f getLookat() const { return lookat; };
    inline Eigen::Vector3f getRight() const { return right; };

private:

    void calcRight() const;

    unsigned int w;
    unsigned int h;
    float fov;
    Eigen::Vector3f centre;
    Eigen::Vector3f up;
    Eigen::Vector3f lookat;
    Eigen::Vector3f right;
};

CAMERAOBJECT_OSTREAM_OP;

#endif