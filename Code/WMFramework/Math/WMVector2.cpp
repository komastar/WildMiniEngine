#include "WMVector2.h"
#include "WMMath.h"
#include "WMVector3.h"
#include "WMVector4.h"
#include "WMMatrix2.h"

using namespace WildMini::Math;

const WMVector2 WMVector2::one = WMVector2(1.0f, 1.0f);
const WMVector2 WMVector2::zero = WMVector2(0.0f, 0.0f);
const WMVector2 WMVector2::left = WMVector2(-1.0f, 0.0f);
const WMVector2 WMVector2::up = WMVector2(0.0f, 1.0f);
const WMVector2 WMVector2::right = WMVector2(1.0f, 0.0f);
const WMVector2 WMVector2::down = WMVector2(0.0f, -1.0f);
const WMVector2 WMVector2::inf = { FLT_MAX, FLT_MAX };
const WMVector2 WMVector2::negInf = { FLT_MIN, FLT_MIN };
const WMVector2 WMVector2::infLeft = { FLT_MIN, 0.0f };
const WMVector2 WMVector2::infUp = { 0.0f, FLT_MAX };
const WMVector2 WMVector2::infRight = { FLT_MAX, 0.0f };
const WMVector2 WMVector2::infDown = { 0.0f, FLT_MIN };

WMVector2 WMVector2::Normalized(WMVector2 v)
{
    WMVector2 normalized(v);
    normalized.Normalize();

    return normalized;
}

float WMVector2::Dot(const WMVector2& v1, const WMVector2& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

const WMVector2& WMVector2::Left()
{
    static const auto left = WMVector2(-1.0f, 0.0f);
    return left;
}

const WMVector2& WMVector2::Right()
{
    static const auto right = WMVector2(1.0f, 0.0f);
    return right;
}

const WMVector2& WMVector2::Up()
{
    static const auto up = WMVector2(0.0f, 1.0f);
    return up;
}

const WMVector2& WMVector2::Down()
{
    static const auto down = WMVector2(0.0f, -1.0f);
    return down;
}

WMVector2::WMVector2()
{
    x = 0.0f;
    y = 0.0f;
}

WMVector2::WMVector2(const WMVector3& v)
{
    x = v.x;
    y = v.y;
}

WMVector2::WMVector2(WMVector4 v)
{
    x = v.x;
    y = v.y;
}

WMVector2::WMVector2(float _x, float _y)
{
    x = _x;
    y = _y;
}

WMVector2::WMVector2(float xy)
{
    x = xy;
    y = xy;
}

float WMVector2::Length()
{
    return sqrtf(x * x + y * y);
}

float WMVector2::LengthSq()
{
    return x * x + y * y;
}

void WMVector2::Normalize()
{
    float inv = 1.0f / sqrtf(x * x + y * y);
    x *= inv;
    y *= inv;
}

bool WMVector2::operator==(const WMVector2& value) const
{
    return x == value.x && y == value.y;
}

bool WMVector2::operator!=(const WMVector2& value) const
{
    return !(*this == value);
}

WMVector2 WMVector2::operator+(const WMVector2& value) const
{
    return WMVector2(x + value.x, y + value.y);
}

WMVector2 WMVector2::operator-(const WMVector2& value) const
{
    return WMVector2(x - value.x, y - value.y);
}

WMVector2 WMVector2::operator*(const float& value) const
{
    return WMVector2(x * value, y * value);
}

const WMVector2& WMVector2::operator+=(const float& value)
{
    this->x = this->x + value;
    this->y = this->y + value;
    return *this;
}

const WMVector2& WMVector2::operator-=(const float& value)
{
    this->x = this->x - value;
    this->y = this->y - value;
    return *this;
}

const WMVector2& WMVector2::operator*=(const float& value)
{
    this->x = this->x * value;
    this->y = this->y * value;
    return *this;
}

const WMVector2& WMVector2::operator/=(const float& value)
{
    float inv = 1.0f / value;
    this->x = this->x / inv;
    this->y = this->y / inv;
    return *this;
}

const WMVector2& WMVector2::operator+=(const WMVector2& value)
{
    this->x = this->x + value.x;
    this->y = this->y + value.y;
    return *this;
}

const WMVector2& WMVector2::operator-=(const WMVector2& value)
{
    this->x = this->x - value.x;
    this->y = this->y - value.y;
    return *this;
}

const WMVector2& WMVector2::operator*=(const WMVector2& value)
{
    this->x = this->x * value.x;
    this->y = this->y * value.y;
    return *this;
}

const WMVector2& WMVector2::operator/=(const WMVector2& value)
{
    this->x = this->x / value.x;
    this->y = this->y / value.y;
    return *this;
}

WMVector2 WMVector2::operator*(const WMMatrix2& value) const
{
    return WMVector2((x * value._11 + y * value._21), (x * value._12 + y * value._22));
}

WMVector2 WMVector2::operator/(const float& value) const
{
    float inv = 1.0f / value;
    return WMVector2(x * inv, y * inv);
}
