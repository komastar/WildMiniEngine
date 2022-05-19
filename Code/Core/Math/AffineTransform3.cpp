#include "Math/Math.h"

AffineTransform3::AffineTransform3()
{
}

AffineTransform3::AffineTransform3(const Matrix3& _m)
{
    m = Matrix3(_m);
}

AffineTransform3 AffineTransform3::Translate(float x, float y, float z)
{
    v.x += x;
    v.y += y;
    v.z += z;

    return *this;
}

AffineTransform3 AffineTransform3::Translate(const Vector3& _v)
{
    v.x += _v.x;
    v.y += _v.y;
    v.z += _v.z;

    return *this;
}

AffineTransform3 AffineTransform3::Multiply(const AffineTransform3& at)
{
    m = m * at.m;
    v = v * at.m + at.v;

    return *this;
}

AffineTransform3 AffineTransform3::Multiply(const LinearTransform3& lt)
{
    m = m * lt.m;
    v = v * lt.m;

    return *this;
}

bool AffineTransform3::operator==(const AffineTransform3& at) const
{
    return m == at.m && v == at.v;
}

bool AffineTransform3::operator!=(const AffineTransform3& at) const
{
    return !(*this == at);
}