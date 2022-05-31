#include "WMMath.h"
#include "WMVector4.h"
#include "WMVector2.h"
#include "WMVector3.h"
#include "WMMatrix4.h"

using namespace WildMini::Math;

const WMVector4 WMVector4::one = { 1.0f, 1.0f, 1.0f, 1.0f };
const WMVector4 WMVector4::zero = { 0.0f, 0.0f, 0.0f, 1.0f };
const WMVector4 WMVector4::left = { -1.0f, 0.0f, 0.0f, 1.0f };
const WMVector4 WMVector4::up = { 0.0f, 1.0f, 0.0f, 1.0f };
const WMVector4 WMVector4::right = { 1.0f, 0.0f, 0.0f, 1.0f };
const WMVector4 WMVector4::down = { 0.0f, -1.0f, 0.0f, 1.0f };
const WMVector4 WMVector4::forward = { 0.0f, 0.0f, 1.0f, 1.0f };
const WMVector4 WMVector4::back = { 0.0f, 0.0f, -1.0f, 1.0f };

WMVector4 WMVector4::Normalized(WMVector4 v)
{
    WMVector4 normalized(v);
    normalized.Normalize();

return normalized;
}

float WMVector4::Dot(const WMVector4& v1, const WMVector4& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

const WMVector4& WMVector4::Forward()
{
    static const auto forward = WMVector4(0.0f, 0.0f, 1.0f, 1.0f);
    return forward;
}

const WMVector4& WMVector4::Backward()
{
    static const auto backward = WMVector4(0.0f, 0.0f, -1.0f, 1.0f);
    return backward;
}

const WMVector4& WMVector4::Left()
{
    static const auto left = WMVector4(1.0f, 0.0f, 0.0f, 1.0f);
    return left;
}

const WMVector4& WMVector4::Right()
{
    static const auto right = WMVector4(-1.0f, 0.0f, 0.0f, 1.0f);
    return right;
}

const WMVector4& WMVector4::Up()
{
    static const auto up = WMVector4(0.0f, 1.0f, 0.0f, 1.0f);
    return up;
}

const WMVector4& WMVector4::Down()
{
    static const auto down = WMVector4(0.0f, -1.0f, 0.0f, 1.0f);
    return down;
}

WMVector4::WMVector4()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}

WMVector4::WMVector4(WMVector2 v)
{
    x = v.x;
    y = v.y;
    z = 0.0f;
    w = 0.0f;
}

WMVector4::WMVector4(WMVector3 v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = 0.0f;
}

WMVector4::WMVector4(float _x, float _y)
{
    x = _x;
    y = _y;
    z = 0.0f;
    w = 0.0f;
}

WMVector4::WMVector4(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
    w = 0.0f;
}

WMVector4::WMVector4(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

WMVector4::WMVector4(float xyzw)
{
    x = xyzw;
    y = xyzw;
    z = xyzw;
    w = xyzw;
}

float WMVector4::Length()
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

float WMVector4::LengthSq()
{
    return x * x + y * y + z * z + w * w;
}

void WMVector4::Normalize()
{
    float inv = 1.0f / sqrtf(x * x + y * y + z * z + w * w);
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
}

bool WMVector4::operator==(const WMVector4& value) const
{
    return x == value.x && y == value.y && z == value.z && w == value.w;
}

bool WMVector4::operator!=(const WMVector4& value) const
{
    return !(*this == value);
}

WMVector4 WMVector4::operator+(const WMVector4& value) const
{
    return WMVector4(x + value.x, y + value.y, z + value.z, w + value.w);
}

WMVector4 WMVector4::operator-(const WMVector4& value) const
{
    return WMVector4(x - value.x, y - value.y, z - value.z, w - value.w);
}

WMVector4 WMVector4::operator*(const float& value) const
{
    return WMVector4(x * value, y * value, z * value, w * value);
}

WMVector4 WMVector4::operator*(const WMMatrix4& value) const
{
    return WMVector4(
        x * value._11 + y * value._21 + z * value._31 + w * value._41,
        x * value._12 + y * value._22 + z * value._32 + w * value._42,
        x * value._13 + y * value._23 + z * value._33 + w * value._43,
        x * value._14 + y * value._24 + z * value._34 + w * value._44
    );
}

WMVector4 WMVector4::operator/(const float& value) const
{
    float inv = 1.0f / value;
    return WMVector4(x * inv, y * inv, z * inv, w * inv);
}
