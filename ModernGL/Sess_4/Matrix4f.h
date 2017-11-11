#include "Vec3f.h"

class Matrix4f
{
    public:
        Matrix4f();
        Matrix4f(float m11, float m12, float m13, float m14,
                 float m21, float m22, float m23, float m24,
                 float m31, float m32, float m33, float m34,
                 float m41, float m42, float m43, float m44);
        Matrix4f(const Matrix4f &mat);
        ~Matrix4f();

    public:
        Matrix4f& operator= (const Matrix4f &r);
        Matrix4f  operator* (const Matrix4f &r) const;
        Matrix4f& operator*=(const Matrix4f &r);
        Vec3f     operator* (const Vec3f   &v)  const;
        // Vec4f     operator* (const Vec4f   &v)  const;

    public:
        const float* getRawPointer() const;

    public:
        static Matrix4f Identity();
        static Matrix4f Translation(float x, float y, float z);
        static Matrix4f Scale(float x, float y, float z);
        static Matrix4f RotationX(float radian);
        static Matrix4f RotationY(float radian);
        static Matrix4f RotationZ(float radian);

    public:
        static Matrix4f lookat(const Vec3f eye, const Vec3f target, const Vec3f up);
        
        static Matrix4f orth(float left, float right, float bottom, float top, float near, float far);
        static Matrix4f frustum(float left, float right, float bottom, float top, float near, float far);
    
    public:
        float m[4][4];

    public:
        static const Matrix4f IDENTITY;
        static const Matrix4f ZERO;
};