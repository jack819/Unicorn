#include "math.h"

class Vec3f 
{
public:
    Vec3f() 
    :x(0.0)
    ,y(0.0)
    ,z(1.0)
    {

    }

    Vec3f(float ax, float ay, float az)
    :x(ax)
    ,y(ay)
    ,z(az)
    {

    }

    Vec3f(const Vec3f &r)
    :x(r.x)
    ,y(r.y)
    ,z(r.z)
    {

    }
    
    ~Vec3f() 
    {

    }

public:
    Vec3f& operator=(const Vec3f &r)
    {
        if (&r != this) {
            x = r.x;
            y = r.y;
            z = r.z;
        }
        return *this;
    }

    bool operator==(const Vec3f &r) const 
    {
        return !(*this != r);
    }

    bool operator!=(const Vec3f &r) const
    {
        return ((x != r.x) || (y != r.y) || (z != r.z));
    }

    Vec3f operator-() const
    {
        return Vec3f(-x, -y, -z);
    }

    Vec3f operator-(const Vec3f &r) const 
    {
        return Vec3f(x - r.x, y - r.y, z - r.z);
    }

    Vec3f operator+(const Vec3f &r) const
    {
        return Vec3f(x + r.x, y + r.x, z + r.z);
    }

    Vec3f operator*(float s) const
    {
        return Vec3f(x * s, y * s, z *s);
    }

    Vec3f& operator+=(const Vec3f& r) 
    {
        x += r.x;
        y += r.y;
        z += r.z;

        return *this;
    }

    Vec3f& operator-=(const Vec3f& r)
    {
        x -= r.x;
        y -= r.y;
        z -= r.z;

        return *this;
    }

    Vec3f& operator*=(float s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

public:
    float length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    float distanceSqr(const Vec3f &r) const 
    {
        return (x - r.x) * (x - r.x) + (y - r.y) * (y - r.y) + (z - r.z) * (z - r.z);
    }

    float dot(const Vec3f &r) const
    {
        return x * r.x + y * r.y + z * r.z;
    }

    Vec3f cross(const Vec3f &r) const
    {
        return Vec3f(
                    y * r.z - z * r.y,
                    z * r.x - x * r.z,
                    x * r.y - y * r.x
                    );
    }

    void normalize()
    {
        float len = length();

        if (len > 0.0000001 || len < -0.0000001)
        {
            len = 1.0f / len;
            x *= len;
            y *= len;
            z *= len;
        }
    }

public:
    float x;
    float y;
    float z;
};