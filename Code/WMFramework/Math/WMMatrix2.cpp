//
//  File:   WMMatrix2.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMMatrix2.h"
#include "WMMath.h"
#include "WMMatrix3.h"
#include "WMMatrix4.h"

using namespace WildMini::Math;

WMMatrix2 WMMatrix2::Inversed(WMMatrix2& m)
{
    WMMatrix2 inversed(m);
    return inversed.Inverse();
}

WMMatrix2 WMMatrix2::Identity()
{
    static WMMatrix2 identity = {
        1.0f, 0.0f
        , 0.0f, 1.0f
    };

    return identity;
}

WMMatrix2::WMMatrix2()
{
    _11 = 1.0f;
    _12 = 0.0f;
    _21 = 0.0f;
    _22 = 1.0f;
}

WMMatrix2::WMMatrix2(float _11, float _12, float _21, float _22)
{
    this->_11 = _11;
    this->_12 = _12;

    this->_21 = _21;
    this->_22 = _22;
}

WMMatrix2::WMMatrix2(const WMMatrix3& m)
{
    _11 = m._11;
    _12 = m._12;

    _21 = m._21;
    _22 = m._22;
}

WMMatrix2::WMMatrix2(const WMMatrix4& m)
{
    _11 = m._11;
    _12 = m._12;

    _21 = m._21;
    _22 = m._22;
}

void WMMatrix2::Transpose()
{
    float t = _12;
    _12 = _21;
    _21 = t;
}

WMMatrix2 WMMatrix2::Inverse()
{
    WMMatrix2 inv;
    inv._11 = _22;
    inv._12 = -_12;
    inv._21 = -_21;
    inv._22 = _11;

    float d = 1.0f / Determinant();
    inv = inv * d;
    for (int y = 0; y < 2; y++)
    {
        for (int x = 0; x < 2; x++)
        {
            m[y][x] = inv.m[y][x];
        }
    }

    return inv;
}

void WMMatrix2::Scale(float x, float y)
{
    _11 = x;
    _22 = y;
}

float WMMatrix2::Determinant()
{
    return (_11 * _22) - (_12 * _21);
}

bool WMMatrix2::operator==(const WMMatrix2& value) const
{
    for (int i = 0; i < 4; i++)
    {
        if (v[i] != value.v[i])
        {
            return false;
        }
    }

    return true;
}

bool WMMatrix2::operator!=(const WMMatrix2& value) const
{
    return !(*this == value);
}

WMMatrix2 WMMatrix2::operator+(const WMMatrix2& value) const
{
    WMMatrix2 add(*this);
    for (int y = 0; y < 2; y++)
    {
        for (int x = 0; x < 2; x++)
        {
            add.m[y][x] += value.m[y][x];
        }
    }

    return add;
}

WMMatrix2 WMMatrix2::operator-(const WMMatrix2& value) const
{
    WMMatrix2 sub(*this);
    for (int y = 0; y < 2; y++)
    {
        for (int x = 0; x < 2; x++)
        {
            sub.m[y][x] -= value.m[y][x];
        }
    }

    return sub;
}

WMMatrix2 WMMatrix2::operator*(const WMMatrix2& value) const
{
    WMMatrix2 mul;
    mul._11 = _11 * value._11 + _12 * value._21;
    mul._12 = _11 * value._12 + _12 * value._22;
    mul._21 = _21 * value._11 + _22 * value._21;
    mul._22 = _21 * value._12 + _22 * value._22;

    return mul;
}

WMMatrix2 WMMatrix2::operator*(const float& value) const
{
    WMMatrix2 mul(*this);
    for (int y = 0; y < 2; y++)
    {
        for (int x = 0; x < 2; x++)
        {
            mul.m[y][x] *= value;
        }
    }

    return mul;
}
