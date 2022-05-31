#include "WMLinearTransform2.h"
#include "WMMath.h"

using namespace WildMini::Math;

WMLinearTransform2::WMLinearTransform2() : m()
{
}

WMLinearTransform2::WMLinearTransform2(const WMMatrix2& _m)
    : m(_m)
{
}

WMLinearTransform2 WMLinearTransform2::Scale(const float& x, const float& y)
{
    m._11 *= x;
    m._12 *= y;
    m._21 *= x;
    m._22 *= y;

    return *this;
}

WMLinearTransform2 WMLinearTransform2::Scale(const WMVector2& v)
{
    m._11 *= v.x;
    m._12 *= v.y;
    m._21 *= v.x;
    m._22 *= v.y;

    return *this;
}

WMLinearTransform2 WMLinearTransform2::Rotate(const float r)
{
    float cos = cosf(r);
    float sin = sinf(r);
    m = m * WMMatrix2(
        cos, sin
        , -sin, cos
    );

    return *this;
}

WMLinearTransform2 WMLinearTransform2::Multiply(const WMMatrix2& _m)
{
    m = m * _m;

    return *this;
}

bool WMLinearTransform2::operator==(const WMLinearTransform2& lt) const
{
    return m == lt.m;
}

bool WMLinearTransform2::operator!=(const WMLinearTransform2& lt) const
{
    return m != lt.m;
}
