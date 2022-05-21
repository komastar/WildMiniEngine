#include "LinearTransform3.h"

using namespace Core::Math;

LinearTransform3::LinearTransform3()
{
}

LinearTransform3::LinearTransform3(const Matrix3& _m)
    : m(_m)
{
}

LinearTransform3 LinearTransform3::Scale(const float& x, const float& y, const float& z)
{
    m._11 *= x;
    m._12 *= y;
    m._13 *= z;

    m._21 *= x;
    m._22 *= y;
    m._23 *= z;

    m._31 *= x;
    m._32 *= y;
    m._33 *= z;

    return *this;
}

LinearTransform3 LinearTransform3::Scale(const Vector3& v)
{
    m._11 *= v.x;
    m._12 *= v.y;
    m._13 *= v.z;

    m._21 *= v.x;
    m._22 *= v.y;
    m._23 *= v.z;

    m._31 *= v.x;
    m._32 *= v.y;
    m._33 *= v.z;

    return *this;
}

LinearTransform3 LinearTransform3::RotateX(float r)
{
    float cos = cosf(r);
    float sin = sinf(r);
    m = m * Matrix3(
        1.0f, 0.0f, 0.0f
        , 0.0f, cos, -sin
        , 0.0f, sin, cos
    );

    return *this;
}

LinearTransform3 LinearTransform3::RotateY(float r)
{
    float cos = cosf(r);
    float sin = sinf(r);
    m = m * Matrix3(
        cos, 0.0f, sin
        , 0.0f, 1.0f, 0.0f
        , -sin, 0.0f, cos
    );

    return *this;
}

LinearTransform3 LinearTransform3::RotateZ(float r)
{
    float cos = cosf(r);
    float sin = sinf(r);
    m = m * Matrix3(
        cos, -sin, 0.0f
        , sin, cos, 0.0f
        , 0.0f, 0.0f, 1.0f
    );

    return *this;
}

LinearTransform3 LinearTransform3::Rotate(const Vector3& axis, float r)
{
    float cos = cosf(r);
    float sin = sinf(r);
    float reverseCos = 1.0f - cos;
    m = m * Matrix3(
        cos + reverseCos * (axis.x * axis.x)
        , reverseCos * (axis.x * axis.y) + (sin * axis.z)
        , reverseCos * (axis.x * axis.z) - (sin * axis.y)
        , reverseCos * (axis.x * axis.y) - (sin * axis.z)
        , cos + reverseCos * (axis.y * axis.y)
        , reverseCos * (axis.y * axis.z) + (sin * axis.x)
        , reverseCos * (axis.x * axis.z) + (sin * axis.y)
        , reverseCos * (axis.y * axis.z) - (sin * axis.x)
        , cos + reverseCos * (axis.z * axis.z));

    return *this;
}

LinearTransform3 LinearTransform3::Multiply(const Matrix3& _m)
{
    m = m * _m;
    return *this;
}

bool LinearTransform3::operator==(const LinearTransform3& lt) const
{
    return m == lt.m;
}

bool LinearTransform3::operator!=(const LinearTransform3& lt) const
{
    return m != lt.m;
}
