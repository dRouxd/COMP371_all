#ifndef RGB_H
#define RGB_H

class RGB
{
public:
    RGB();
    RGB(float r, float g, float b);
    RGB(const RGB& rgb);
    RGB& operator=(const RGB& rgb);
    RGB& operator+=(const RGB& rgb);
    RGB& operator*=(const RGB& rgb);
    RGB& operator*=(float s);
    float& operator()(int i);
    float operator()(int i) const;

    inline float getR() const { return r; };
    inline float getG() const { return g; };
    inline float getB() const { return b; };

private:
    float r;
    float g;
    float b;

    friend RGB operator+(RGB rgb, int s);
    friend RGB operator+(RGB rgb1, const RGB& rgb2);
    friend RGB operator*(RGB rgb, int s);
    friend RGB operator*(RGB rgb, unsigned int s);
    friend RGB operator*(RGB rgb, float s);
    friend RGB operator*(RGB rgb1, const RGB& rgb2);

};

RGB operator+(RGB rgb, int s);
RGB operator+(RGB rgb1, const RGB& rgb2);
RGB operator*(RGB rgb, int s);
RGB operator*(RGB rgb, unsigned int s);
RGB operator*(RGB rgb, float s);
RGB operator*(RGB rgb1, const RGB& rgb2);

#endif