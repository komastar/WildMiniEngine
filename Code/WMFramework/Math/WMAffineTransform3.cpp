#include "WMAffineTransform3.h"

using namespace WildMini::Math;

WMAffineTransform3::WMAffineTransform3()
{
}

WMAffineTransform3::WMAffineTransform3(const WMMatrix3& _m)
    : m(_m)
{
}

WMAffineTransform3 WMAffineTransform3::Translate(float x, float y, float z)
{
    v.x += x;
    v.y += y;
    v.z += z;

    return *this;
}

WMAffineTransform3 WMAffineTransform3::Translate(const WMVector3& _v)
{
    v.x += _v.x;
    v.y += _v.y;
    v.z += _v.z;

    return *this;
}

WMAffineTransform3 WMAffineTransform3::Multiply(const WMAffineTransform3& at)
{
    m = m * at.m;
    v = v * at.m + at.v;

    return *this;
}

WMAffineTransform3 WMAffineTransform3::Multiply(const WMLinearTransform3& lt)
{
    m = m * lt.m;
    v = v * lt.m;

    return *this;
}

bool WMAffineTransform3::operator==(const WMAffineTransform3& at) const
{
    return m == at.m && v == at.v;
}

bool WMAffineTransform3::operator!=(const WMAffineTransform3& at) const
{
    return !(*this == at);
}
