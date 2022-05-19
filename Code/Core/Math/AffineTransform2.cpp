#include "Math/Math.h"

AffineTransform2::AffineTransform2() : m()
{
}

AffineTransform2::AffineTransform2(const Matrix3& _m)
{
    m = Matrix2(_m);
    v = Vector2(_m._31, _m._32);
}

AffineTransform2 AffineTransform2::Translate(float x, float y)
{
    v.x += x;
    v.y += y;

    return *this;
}

AffineTransform2 AffineTransform2::Translate(const Vector2& _v)
{
    v.x += _v.x;
    v.y += _v.y;

    return *this;
}

AffineTransform2 AffineTransform2::Multiply(const AffineTransform2& at)
{
    m = m * at.m;
    v = v * at.m + at.v;

    return *this;
}

AffineTransform2 AffineTransform2::Multiply(const LinearTransform2& lt)
{
    m = m * lt.m;
    v = v * lt.m;

    return *this;
}

bool AffineTransform2::operator==(const AffineTransform2& at) const
{
    return m == at.m && v == at.v;
}

bool AffineTransform2::operator!=(const AffineTransform2& at) const
{
    return !(*this == at);
}
