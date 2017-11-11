#include "string.h"
#include "Matrix4f.h"
#include "math.h"

const Matrix4f Matrix4f::IDENTITY = Matrix4f(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0);

const Matrix4f Matrix4f::ZERO = Matrix4f(
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0);

Matrix4f::Matrix4f()
{
    *this = IDENTITY;
}

Matrix4f::Matrix4f(float m11, float m12, float m13, float m14,
                 float m21, float m22, float m23, float m24,
                 float m31, float m32, float m33, float m34,
                 float m41, float m42, float m43, float m44)
{
    m[0][0] = m11;
    m[0][1] = m12;
    m[0][2] = m13;
    m[0][3] = m14;

    m[1][0] = m21;
    m[1][1] = m22;
    m[1][2] = m23;
    m[1][3] = m24;

    m[2][0] = m31;
    m[2][1] = m32;
    m[2][2] = m33;
    m[2][3] = m34;

    m[3][0] = m41;
    m[3][1] = m42;
    m[3][2] = m43;
    m[3][3] = m44;
}

Matrix4f::Matrix4f(const Matrix4f &mat)
{
    memcpy(m, mat.m, sizeof(mat.m));
}

Matrix4f::~Matrix4f()
{

}

Matrix4f& Matrix4f::operator= (const Matrix4f &r)
{
    if (&r != this)
    {
        memcpy(m, r.m, sizeof(r.m));
    }

    return *this;
}

Matrix4f  Matrix4f::operator* (const Matrix4f &r) const
{
    Matrix4f mat;
    mat.m[0][0] = m[0][0] * r.m[0][0] + m[0][1] * r.m[1][0] + m[0][2] * r.m[2][0] + m[0][3] * r.m[3][0];
    mat.m[0][1] = m[0][0] * r.m[0][1] + m[0][1] * r.m[1][1] + m[0][2] * r.m[2][1] + m[0][3] * r.m[3][1];
    mat.m[0][2] = m[0][0] * r.m[0][2] + m[0][1] * r.m[1][2] + m[0][2] * r.m[2][2] + m[0][3] * r.m[3][2];
    mat.m[0][3] = m[0][0] * r.m[0][3] + m[0][1] * r.m[1][3] + m[0][2] * r.m[2][3] + m[0][3] * r.m[3][3];

    mat.m[1][0] = m[1][0] * r.m[0][0] + m[1][1] * r.m[1][0] + m[1][2] * r.m[2][0] + m[1][3] * r.m[3][0];
    mat.m[1][1] = m[1][0] * r.m[0][1] + m[1][1] * r.m[1][1] + m[1][2] * r.m[2][1] + m[1][3] * r.m[3][1];
    mat.m[1][2] = m[1][0] * r.m[0][2] + m[1][1] * r.m[1][2] + m[1][2] * r.m[2][2] + m[1][3] * r.m[3][2];
    mat.m[1][3] = m[1][0] * r.m[0][3] + m[1][1] * r.m[1][3] + m[1][2] * r.m[2][3] + m[1][3] * r.m[3][3];

    mat.m[2][0] = m[2][0] * r.m[0][0] + m[2][1] * r.m[1][0] + m[2][2] * r.m[2][0] + m[2][3] * r.m[3][0];
    mat.m[2][1] = m[2][0] * r.m[0][1] + m[2][1] * r.m[1][1] + m[2][2] * r.m[2][1] + m[2][3] * r.m[3][1];
    mat.m[2][2] = m[2][0] * r.m[0][2] + m[2][1] * r.m[1][2] + m[2][2] * r.m[2][2] + m[2][3] * r.m[3][2];
    mat.m[2][3] = m[2][0] * r.m[0][3] + m[2][1] * r.m[1][3] + m[2][2] * r.m[2][3] + m[2][3] * r.m[3][3];

    mat.m[3][0] = m[3][0] * r.m[0][0] + m[3][1] * r.m[1][0] + m[3][2] * r.m[2][0] + m[3][3] * r.m[3][0];
    mat.m[3][1] = m[3][0] * r.m[0][1] + m[3][1] * r.m[1][1] + m[3][2] * r.m[2][1] + m[3][3] * r.m[3][1];
    mat.m[3][2] = m[3][0] * r.m[0][2] + m[3][1] * r.m[1][2] + m[3][2] * r.m[2][2] + m[3][3] * r.m[3][2];
    mat.m[3][3] = m[3][0] * r.m[0][3] + m[3][1] * r.m[1][3] + m[3][2] * r.m[2][3] + m[3][3] * r.m[3][3];

    return mat;
}

Matrix4f&  Matrix4f::operator*=(const Matrix4f &r)
{
    *this = *this * r;
    return *this;
}

Vec3f   Matrix4f::operator* (const Vec3f   &v)  const
{
    float w_length = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + 1.0 * m[3][3];
    if (w_length < 0.0000001 && w_length > 0.0000001) {
        return v;
    }
    else {
        Vec3f result = Vec3f( (v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2]) / w_length,
                              (v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2]) / w_length,
                              (v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2]) / w_length );
        return result;
    }
}

// Vec4f   Matrix4f::operator* (const Vec4f   &v)  const;
// {
//     return Vec4<T>(
//                     (v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + v.w * m[0][3]),
//                     (v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + v.w * m[1][3]),
//                     (v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + v.w * m[2][3]),
//                     (v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + v.w * m[3][3]),
//                     );
// }

const float* Matrix4f::getRawPointer() const
{
    return &(m[0][0]);
}

Matrix4f Matrix4f::Identity()
{
    return Matrix4f::IDENTITY;
}

Matrix4f Matrix4f::Translation(float x, float y, float z)
{
    return Matrix4f(1, 0, 0, x,
                    0, 1, 0, y,
                    0, 0, 1, z,
                    0, 0, 0, 1);
}

Matrix4f Matrix4f::Scale(float x, float y, float z)
{
    return Matrix4f(x, 0, 0, 0,
                    0, y, 0, 0,
                    0, 0, z, 0,
                    0, 0, 0, 1);
}

Matrix4f Matrix4f::RotationX(float radian)
{
    return Matrix4f(1, 0, 0, 0,
                    0, cos(radian), -sin(radian), 0,
                    0, sin(radian), cos(radian), 0,
                    0, 0, 0, 1);
}

Matrix4f Matrix4f::RotationY(float radian)
{
    return Matrix4f(cos(radian), 0, sin(radian), 0,
                    0, 1, 0, 0,
                    -sin(radian), 0, cos(radian), 0,
                    0, 0, 0, 1);
}

Matrix4f Matrix4f::RotationZ(float radian)
{
    return Matrix4f(cos(radian), -sin(radian), 0, 0,
                    sin(radian), cos(radian), 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
}

Matrix4f Matrix4f::lookat(const Vec3f eye, const Vec3f target, const Vec3f up)
{
    Vec3f xAxis;
    Vec3f yAxis;
    Vec3f zAxis(eye - target);

    zAxis.normalize();

    xAxis = up.cross(zAxis);
    xAxis.normalize();

    yAxis = zAxis.cross(xAxis);

    Matrix4f mat(
                 xAxis.x, xAxis.y, xAxis.z, -eye.dot(xAxis),
                 yAxis.x, yAxis.y, yAxis.z, -eye.dot(yAxis),
                 zAxis.x, zAxis.y, zAxis.z, -eye.dot(zAxis),
                 0, 0, 0, 1);
    return mat;
}

Matrix4f Matrix4f::orth(float left, float right, float bottom, float top, float near, float far)
{
    float x = 2.0 / (right - left);
    float y = 2.0 / (top - bottom);
    float a = - (right + left) / (right - left);
    float b = - (top + bottom) / (top - bottom);
    float c = - 2.0 / (far - near);
    float d = - (far + near) / (far - near);

    Matrix4f mat(
                x, 0, 0, a,
                0, y, 0, b,
                0, 0, c, d,
                0, 0, 0, 1
                );
    return mat;
}

Matrix4f Matrix4f::frustum(float left, float right, float bottom, float top, float near, float far)
{
    float x, y, a, b, c, d;

    x = (2.0 * near) / (right - left);
    y = (2.0 * near) / (top - bottom);
    a = (right + left) / (right - left);
    b = (top + bottom) / (top - bottom);
    c = -(far + near) / ( far - near);
    d = -(2.0 * far * near) / (far - near);

    Matrix4f mat(
                x, 0, a, 0,
                0, y, b, 0,
                0, 0, c, d,
                0, 0, -1, 0
                );
    return mat;
}