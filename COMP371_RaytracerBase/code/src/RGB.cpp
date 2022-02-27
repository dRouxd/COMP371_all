
#include "RGB.h"

#include <stdexcept>

RGB::RGB()
{
    this->r = 0.0f;
    this->g = 0.0f;
    this->b = 0.0f;
}

RGB::RGB(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

RGB::RGB(const RGB& rgb)
{
    this->r = rgb.r;
    this->g = rgb.g;
    this->b = rgb.b;
}

RGB& RGB::operator=(const RGB& rgb)
{
    this->r = rgb.r;
    this->g = rgb.g;
    this->b = rgb.b;
}

RGB& RGB::operator+=(const RGB& rgb)
{
    this->r += rgb.r;
    this->g += rgb.g;
    this->b += rgb.b;
    return *this;
}

RGB& RGB::operator*=(const RGB& rgb)
{
    this->r *= rgb.r;
    this->g *= rgb.g;
    this->b *= rgb.b;
    return *this;
}

RGB& RGB::operator*=(float s)
{
    this->r *= s;
    this->g *= s;
    this->b *= s;
    return *this;
}

float& RGB::operator()(int i)
{
    switch (i)
    {
    case 0:
        return this->r;
    case 1:
        return this->g;
    case 2:
        return this->b;
    default:
        throw std::out_of_range("RGB out of range exception.");
    }
}

float RGB::operator()(int i) const
{
    switch (i)
    {
    case 0:
        return this->r;
    case 1:
        return this->g;
    case 2:
        return this->b;
    default:
        throw std::out_of_range("RGB out of range exception.");
    }
}

RGB operator+(RGB rgb, int s)
{
    rgb.r += s;
    rgb.g += s;
    rgb.b += s;
    return rgb;
}

RGB operator+(RGB rgb1, const RGB& rgb2)
{
    rgb1.r += rgb2.r;
    rgb1.g += rgb2.g;
    rgb1.b += rgb2.b;
    return rgb1;
}

RGB operator*(RGB rgb, int s)
{
    rgb.r *= s;
    rgb.g *= s;
    rgb.b *= s;
    return rgb;
}

RGB operator*(RGB rgb, unsigned int s)
{
    rgb.r *= s;
    rgb.g *= s;
    rgb.b *= s;
    return rgb;
}

RGB operator*(RGB rgb, float s)
{
    rgb.r *= s;
    rgb.g *= s;
    rgb.b *= s;
    return rgb;
}

RGB operator*(int s, RGB rgb)
{
    rgb *= s;
    return rgb;
}

RGB operator*(unsigned int s, RGB rgb)
{
    rgb *= s;
    return rgb;
}

RGB operator*(float s, RGB rgb)
{
    rgb *= s;
    return rgb;
}


RGB operator*(RGB rgb1, const RGB& rgb2)
{
    rgb1.r *= rgb2.r;
    rgb1.g *= rgb2.g;
    rgb1.b *= rgb2.b;
    return rgb1;
}

std::ostream& operator<<(std::ostream& os, const RGB rgb)
{
    os << "[" << rgb.r << ", " << rgb.g << ", " << rgb.b << "]";
    return os;
}