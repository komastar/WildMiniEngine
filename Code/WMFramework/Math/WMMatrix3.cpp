//
//  File:   WMMatrix3.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMMatrix3.h"
#include "WMMatrix2.h"
#include "WMMatrix4.h"

using namespace WildMini;

WMMatrix3 WMMatrix3::Inversed(WMMatrix3& m)
{
    return m.Inverse();
}

WMMatrix3 WMMatrix3::Identity()
{
    static WMMatrix3 identity = {
        1.0f, 0.0f, 0.0f
        , 0.0f, 1.0f, 0.0f
        , 0.0f, 0.0f, 1.0f
    };

    return identity;
}

WMMatrix3 WMMatrix3::Transposed(WMMatrix3& m)
{
    WMMatrix3 transposed(m);
    m.Transpose();

    return transposed;
}

WMMatrix3::WMMatrix3()
{
    _11 = 1.0f;
    _12 = 0.0f;
    _13 = 0.0f;

    _21 = 0.0f;
    _22 = 1.0f;
    _23 = 0.0f;
    
    _31 = 0.0f;
    _32 = 0.0f;
    _33 = 1.0f;
}

WMMatrix3::WMMatrix3(float _11, float _12, float _13, float _21, float _22, float _23, float _31, float _32, float _33)
{
    this->_11 = _11;
    this->_12 = _12;
    this->_13 = _13;

    this->_21 = _21;
    this->_22 = _22;
    this->_23 = _23;

    this->_31 = _31;
    this->_32 = _32;
    this->_33 = _33;
}

WMMatrix3::WMMatrix3(const WMMatrix2& m)
{
    _11 = m._11;
    _12 = m._12;
    _13 = 0.0f;

    _21 = m._21;
    _22 = m._22;
    _23 = 0.0f;

    _31 = 0.0f;
    _32 = 0.0f;
    _33 = 0.0f;
}

WMMatrix3::WMMatrix3(const WMMatrix4& m)
{
    _11 = m._11;
    _12 = m._12;
    _13 = m._13;

    _21 = m._21;
    _22 = m._22;
    _23 = m._23;

    _31 = m._31;
    _32 = m._32;
    _33 = m._33;
}

WMMatrix3 WMMatrix3::Transpose()
{
    return {
        _11, _21, _31,
        _12, _22, _32,
        _13, _23, _33
    };
}

WMMatrix3 WMMatrix3::Inverse()
{
    float d = Determinant();
    if (0.0f != d)
    {
        float invDet = 1.0f / d;
        WMMatrix3 inv;
        inv._11 = (_22 * _33 - _32 * _23) * invDet;
        inv._12 = (_32 * _13 - _12 * _33) * invDet;
        inv._13 = (_12 * _23 - _22 * _13) * invDet;
        inv._21 = (_31 * _23 - _21 * _33) * invDet;
        inv._22 = (_11 * _33 - _31 * _13) * invDet;
        inv._23 = (_21 * _13 - _11 * _23) * invDet;
        inv._31 = (_21 * _32 - _31 * _22) * invDet;
        inv._32 = (_31 * _12 - _11 * _32) * invDet;
        inv._33 = (_11 * _22 - _21 * _12) * invDet;
        return inv;
    }
    
    return WMMatrix3();
}

float WMMatrix3::Determinant()
{
    return (_11 * _22 * _33) +
        (_21 * _32 * _13) +
        (_31 * _12 * _23) -
        (_31 * _22 * _13) -
        (_21 * _12 * _33) -
        (_11 * _32 * _23);
}

WMMatrix3 WMMatrix3::Adjoint()
{
    WMMatrix3 adj;
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            adj.m[y][x] = Cofactor(y, x);
        }
    }
    adj.Transpose();

    return adj;
}

float WMMatrix3::Cofactor(int y, int x)
{
    float cof = Minor(y, x);
    if (((y + x) % 2) == 1)
    {
        cof *= -1.0f;
    }

    return cof;
}

float WMMatrix3::Minor(int _y, int _x)
{
    float min = 0.0f;
    int i = 0;
    float fm[4] = { 0.0f };
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            if (y != _y && x != _x)
            {
                fm[i] = m[y][x];
                ++i;
            }
        }
    }
    min = fm[0] * fm[3] - fm[1] * fm[2];

    return min;
}

bool WMMatrix3::operator==(const WMMatrix3& value) const
{
    for (int i = 0; i < 9; i++)
    {
        if (v[i] != value.v[i])
        {
            return false;
        }
    }

    return true;
}

bool WMMatrix3::operator!=(const WMMatrix3& value) const
{
    return !(*this == value);
}

WMMatrix3 WMMatrix3::operator+(const WMMatrix3& value) const
{
    WMMatrix3 add(*this);
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            add.m[y][x] += value.m[y][x];
        }
    }

    return add;
}

WMMatrix3 WMMatrix3::operator-(const WMMatrix3& value) const
{
    WMMatrix3 sub(*this);
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            sub.m[y][x] -= value.m[y][x];
        }
    }

    return sub;
}

WMMatrix3 WMMatrix3::operator*(const WMMatrix3& value) const
{
    WMMatrix3 mul;
    mul._11 = _11 * value._11 + _12 * value._21 + _13 * value._31;
    mul._12 = _11 * value._12 + _12 * value._22 + _13 * value._32;
    mul._13 = _11 * value._13 + _12 * value._23 + _13 * value._33;

    mul._21 = _21 * value._11 + _22 * value._21 + _23 * value._31;
    mul._22 = _21 * value._12 + _22 * value._22 + _23 * value._32;
    mul._23 = _21 * value._13 + _22 * value._23 + _23 * value._33;

    mul._31 = _31 * value._11 + _32 * value._21 + _33 * value._31;
    mul._32 = _31 * value._12 + _32 * value._22 + _33 * value._32;
    mul._33 = _31 * value._13 + _32 * value._23 + _33 * value._33;

    return mul;
}

WMMatrix3 WMMatrix3::operator*(const float& value) const
{
    WMMatrix3 mul(*this);
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            mul.m[y][x] *= value;
        }
    }

    return mul;
}
