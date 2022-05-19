#include "Math/Math.h"

LinearTransform2::LinearTransform2() : m()
{
}

LinearTransform2::LinearTransform2(const Matrix2& _m)
{
    m = Matrix2(_m);
}

LinearTransform2 LinearTransform2::Scale(const float& x, const float& y)
{
    m._11 *= x;
    m._12 *= y;
    m._21 *= x;
    m._22 *= y;

    return *this;
}

LinearTransform2 LinearTransform2::Scale(const Vector2& v)
{
    m._11 *= v.x;
    m._12 *= v.y;
    m._21 *= v.x;
    m._22 *= v.y;

    return *this;
}

LinearTransform2 LinearTransform2::Rotate(const float r)
{
    float cos = cosf(r);
    float sin = sinf(r);
    m = m * Matrix2(
        cos, sin
        , -sin, cos
    );

    return *this;
}

LinearTransform2 LinearTransform2::Multiply(const Matrix2& _m)
{
    m = m * _m;

    return *this;
}

bool LinearTransform2::operator==(const LinearTransform2& lt) const
{
    return m == lt.m;
}

bool LinearTransform2::operator!=(const LinearTransform2& lt) const
{
    return m != lt.m;
}