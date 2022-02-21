#ifndef RAY_H
#define RAY_H

#include <Eigen/Core>

class Ray
{
public:
    Ray(Eigen::Vector3f origin, Eigen::Vector3f direction, Eigen::Vector3f color = Eigen::Vector3f(1, 0.149, 0.9));
    Ray(const Ray& r);
    ~Ray() = default;
    void print();

    inline Eigen::Vector3f getDirection() const { return direction; };
    inline Eigen::Vector3f getOrigin() const { return origin; };
    inline Eigen::Vector3f getColor() const { return color; };

private:
    Eigen::Vector3f origin;
    Eigen::Vector3f direction;
    Eigen::Vector3f color;

};



#endif