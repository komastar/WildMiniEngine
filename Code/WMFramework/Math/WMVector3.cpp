//
//  File:   WMVector3.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMVector3.h"
#include "WMMath.h"
#include "WMVector2.h"
#include "WMVector4.h"
#include "WMMatrix3.h"

using namespace WildMini;

const WMVector3 WMVector3::one = { 1.0f, 1.0f, 1.0f };
const WMVector3 WMVector3::zero = { 0.0f, 0.0f, 0.0f };
const WMVector3 WMVector3::left = { -1.0f, 0.0f, 0.0f };
const WMVector3 WMVector3::up = { 0.0f, 1.0f, 0.0f };
const WMVector3 WMVector3::right = { 1.0f, 0.0f, 0.0f };
const WMVector3 WMVector3::down = { 0.0f, -1.0f, 0.0f };
const WMVector3 WMVector3::forward = { 0.0f, 0.0f, 1.0f };
const WMVector3 WMVector3::back = { 0.0f, 0.0f, -1.0f };

WMVector3 WMVector3::Normalized(WMVector3 v)
{
    WMVector3 normalized(v);
    normalized.Normalize();

    return normalized;
}

float WMVector3::Dot(const WMVector3& v1, const WMVector3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

WMVector3 WMVector3::Cross(const WMVector3& v1, const WMVector3& v2)
{
    return WMVector3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

const WMVector3& WMVector3::Forward()
{
    static const auto forward = WMVector3(0.0f, 0.0f, 1.0f);
    return forward;
}

const WMVector3& WMVector3::Backward()
{
    static const auto backward = WMVector3(0.0f, 0.0f, -1.0f);
    return backward;
}

const WMVector3& WMVector3::Left()
{
    static const auto left = WMVector3(1.0f, 0.0f, 0.0f);
    return left;
}

const WMVector3& WMVector3::Right()
{
    static const auto right = WMVector3(-1.0f, 0.0f, 0.0f);
    return right;
}

const WMVector3& WMVector3::Up()
{
    static const auto up = WMVector3(0.0f, 1.0f, 0.0f);
    return up;
}

const WMVector3& WMVector3::Down()
{
    static const auto down = WMVector3(0.0f, -1.0f, 0.0f);
    return down;
}

WMVector3::WMVector3()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

WMVector3::WMVector3(WMVector2 v)
{
    x = v.x;
    y = v.y;
    z = 0.0f;
}

WMVector3::WMVector3(WMVector4 v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

WMVector3::WMVector3(float _x, float _y)
{
    x = _x;
    y = _y;
    z = 0.0f;
}

WMVector3::WMVector3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

WMVector3::WMVector3(float xyz)
{
    x = xyz;
    y = xyz;
    z = xyz;
}

float WMVector3::Length()
{
    return sqrtf(x * x + y * y + z * z);
}

float WMVector3::LengthSq()
{
    return x * x + y * y + z * z;
}

const WMVector3& WMVector3::Normalize()
{
    float inv = 1.0f / sqrtf(x * x + y * y + z * z);
    x *= inv;
    y *= inv;
    z *= inv;

    return *this;
}

bool WMVector3::operator==(const WMVector3& value) const
{
    return x == value.x && y == value.y && z == value.z;
}

bool WMVector3::operator!=(const WMVector3& value) const
{
    return !(*this == value);
}

WMVector3 WMVector3::operator+(const WMVector3& value) const
{
    return WMVector3(x + value.x, y + value.y, z + value.z);
}

WMVector3 WMVector3::operator-(const WMVector3& value) const
{
    return WMVector3(x - value.x, y - value.y, z - value.z);
}

WMVector3 WMVector3::operator-() const
{
    return WMVector3(-x, -y, -z);
}

WMVector3 WMVector3::operator*(const float& value) const
{
    return WMVector3(x * value, y * value, z * value);
}

WMVector3 WMVector3::operator*(const WMMatrix3& value) const
{
    return WMVector3(
        x * value._11 + y * value._21 + z * value._31,
        x * value._12 + y * value._22 + z * value._32,
        x * value._13 + y * value._23 + z * value._33
    );
}

WMVector3 WMVector3::operator/(const float& value) const
{
    float inv = 1.0f / value;
    return WMVector3(x * inv, y * inv, z * inv);
}
