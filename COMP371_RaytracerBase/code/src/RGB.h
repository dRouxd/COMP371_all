#ifndef RGB_H
#define RGB_H

#include <iostream>

class RGB
{
public:
    RGB();
    RGB(float r, float g, float b);
    RGB(const RGB& rgb);
    void clamp(float min = 0.0f, float max = 1.0f);

    inline float getR() const { return r; };
    inline float getG() const { return g; };
    inline float getB() const { return b; };

    RGB& operator=(const RGB& rgb);
    RGB& operator+=(const RGB& rgb);
    RGB& operator*=(const RGB& rgb);
    RGB& operator*=(float s);
    float& operator()(int i);
    float operator()(int i) const;

private:
    float r;
    float g;
    float b;

    friend RGB operator+(RGB rgb, int s);
    friend RGB operator+(RGB rgb1, const RGB& rgb2);
    friend RGB operator*(RGB rgb, int s);
    friend RGB operator*(RGB rgb, unsigned int s);
    friend RGB operator*(RGB rgb, float s);
    friend RGB operator*(int s, RGB rgb);
    friend RGB operator*(unsigned int s, RGB rgb);
    friend RGB operator*(float s, RGB rgb);
    friend RGB operator*(RGB rgb1, const RGB& rgb2);
    friend std::ostream& operator<<(std::ostream& os, const RGB rgb);

};

RGB operator+(RGB rgb, int s);
RGB operator+(RGB rgb1, const RGB& rgb2);
RGB operator*(RGB rgb, int s);
RGB operator*(RGB rgb, unsigned int s);
RGB operator*(RGB rgb, float s);
RGB operator*(int s, RGB rgb);
RGB operator*(unsigned int s, RGB rgb);
RGB operator*(float s, RGB rgb);
RGB operator*(RGB rgb1, const RGB& rgb2);
std::ostream& operator<<(std::ostream& os, const RGB rgb);

#endif