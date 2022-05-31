#include "WMMatrix4.h"
#include "WMMath.h"
#include "WMVector3.h"
#include "WMMatrix2.h"
#include "WMMatrix3.h"

using namespace WildMini::Math;

WMMatrix4 WMMatrix4::Inversed(WMMatrix4& m)
{
    WMMatrix4 inversed(m);
    return inversed.Inverse();
}

WMMatrix4 WMMatrix4::Identity()
{
    static WMMatrix4 mat = {
        1.0f, 0.0f, 0.0f, 0.0f
        , 0.0f, 1.0f, 0.0f, 0.0f
        , 0.0f, 0.0f, 1.0f, 0.0f
        , 0.0f, 0.0f, 0.0f, 1.0f
    };

    return mat;
}

WMMatrix4 WMMatrix4::Transposed(WMMatrix4& m)
{
    WMMatrix4 transposed(m);
    transposed.Transpose();

    return transposed;
}

WMMatrix4::WMMatrix4()
{
    _11 = 1.0f;
    _12 = 0.0f;
    _13 = 0.0f;
    _14 = 0.0f;

    _21 = 0.0f;
    _22 = 1.0f;
    _23 = 0.0f;
    _24 = 0.0f;
    
    _31 = 0.0f;
    _32 = 0.0f;
    _33 = 1.0f;
    _34 = 0.0f;
    
    _41 = 0.0f;
    _42 = 0.0f;
    _43 = 0.0f;
    _44 = 1.0f;
}

WMMatrix4::WMMatrix4(float _11, float _12, float _13, float _14
    , float _21, float _22, float _23, float _24
    , float _31, float _32, float _33, float _34
    , float _41, float _42, float _43, float _44)
{
    this->_11 = _11;
    this->_12 = _12;
    this->_13 = _13;
    this->_14 = _14;

    this->_21 = _21;
    this->_22 = _22;
    this->_23 = _23;
    this->_24 = _24;

    this->_31 = _31;
    this->_32 = _32;
    this->_33 = _33;
    this->_34 = _34;

    this->_41 = _41;
    this->_42 = _42;
    this->_43 = _43;
    this->_44 = _44;
}

WMMatrix4::WMMatrix4(const WMMatrix2& m)
{
    _11 = m._11;
    _12 = m._12;
    _13 = 0.0f;
    _14 = 0.0f;

    _21 = m._21;
    _22 = m._22;
    _23 = 0.0f;
    _24 = 0.0f;

    _31 = 0.0f;
    _32 = 0.0f;
    _33 = 0.0f;
    _34 = 0.0f;

    _41 = 0.0f;
    _42 = 0.0f;
    _43 = 0.0f;
    _44 = 0.0f;
}

WMMatrix4::WMMatrix4(const WMMatrix3& m)
{
    _11 = m._11;
    _12 = m._12;
    _13 = m._13;
    _14 = 0.0f;

    _21 = m._21;
    _22 = m._22;
    _23 = m._23;
    _24 = 0.0f;

    _31 = m._31;
    _32 = m._32;
    _33 = m._33;
    _34 = 0.0f;

    _41 = 0.0f;
    _42 = 0.0f;
    _43 = 0.0f;
    _44 = 0.0f;
}

void WMMatrix4::Transpose()
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            float t = m[y][x];
            m[y][x] = m[x][y];
            m[x][y] = t;
        }
    }
}

WMMatrix4 WMMatrix4::Inverse()
{
    float d = Determinant();
    if (0.0f != d)
    {
        float invDet = 1.0f / d;
        WMMatrix4 inv;
        inv._11 = ((_23 * _34 * _42) - (_24 * _33 * _42) + (_24 * _32 * _43) - (_22 * _34 * _43) - (_23 * _32 * _44) + (_22 * _33 * _44)) * invDet;
        inv._12 = ((_14 * _33 * _42) - (_13 * _34 * _42) - (_14 * _32 * _43) + (_12 * _34 * _43) + (_13 * _32 * _44) - (_12 * _33 * _44)) * invDet;
        inv._13 = ((_13 * _24 * _42) - (_14 * _23 * _42) + (_14 * _22 * _43) - (_12 * _24 * _43) - (_13 * _22 * _44) + (_12 * _23 * _44)) * invDet;
        inv._14 = ((_14 * _23 * _32) - (_13 * _24 * _32) - (_14 * _22 * _33) + (_12 * _24 * _33) + (_13 * _22 * _34) - (_12 * _23 * _34)) * invDet;
        inv._21 = ((_24 * _33 * _41) - (_23 * _34 * _41) - (_24 * _31 * _43) + (_21 * _34 * _43) + (_23 * _31 * _44) - (_21 * _33 * _44)) * invDet;
        inv._22 = ((_13 * _34 * _41) - (_14 * _33 * _41) + (_14 * _31 * _43) - (_11 * _34 * _43) - (_13 * _31 * _44) + (_11 * _33 * _44)) * invDet;
        inv._23 = ((_14 * _23 * _41) - (_13 * _24 * _41) - (_14 * _21 * _43) + (_11 * _24 * _43) + (_13 * _21 * _44) - (_11 * _23 * _44)) * invDet;
        inv._24 = ((_13 * _24 * _31) - (_14 * _23 * _31) + (_14 * _21 * _33) - (_11 * _24 * _33) - (_13 * _21 * _34) + (_11 * _23 * _34)) * invDet;
        inv._31 = ((_22 * _34 * _41) - (_24 * _32 * _41) + (_24 * _31 * _42) - (_21 * _34 * _42) - (_22 * _31 * _44) + (_21 * _32 * _44)) * invDet;
        inv._32 = ((_14 * _32 * _41) - (_12 * _34 * _41) - (_14 * _31 * _42) + (_11 * _34 * _42) + (_12 * _31 * _44) - (_11 * _32 * _44)) * invDet;
        inv._33 = ((_12 * _24 * _41) - (_14 * _22 * _41) + (_14 * _21 * _42) - (_11 * _24 * _42) - (_12 * _21 * _44) + (_11 * _22 * _44)) * invDet;
        inv._34 = ((_14 * _22 * _31) - (_12 * _24 * _31) - (_14 * _21 * _32) + (_11 * _24 * _32) + (_12 * _21 * _34) - (_11 * _22 * _34)) * invDet;
        inv._41 = ((_23 * _32 * _41) - (_22 * _33 * _41) - (_23 * _31 * _42) + (_21 * _33 * _42) + (_22 * _31 * _43) - (_21 * _32 * _43)) * invDet;
        inv._42 = ((_12 * _33 * _41) - (_13 * _32 * _41) + (_13 * _31 * _42) - (_11 * _33 * _42) - (_12 * _31 * _43) + (_11 * _32 * _43)) * invDet;
        inv._43 = ((_13 * _22 * _41) - (_12 * _23 * _41) - (_13 * _21 * _42) + (_11 * _23 * _42) + (_12 * _21 * _43) - (_11 * _22 * _43)) * invDet;
        inv._44 = ((_12 * _23 * _31) - (_13 * _22 * _31) + (_13 * _21 * _32) - (_11 * _23 * _32) - (_12 * _21 * _33) + (_11 * _22 * _33)) * invDet;

        return inv;
    }

    return WMMatrix4();
}

const WMMatrix4& WMMatrix4::View(const WMVector3& eye, const WMVector3& lookat, const WMVector3& up)
{
    WMVector3 l = (lookat - eye).Normalize();
    WMVector3 r = WMVector3::Cross(up, l).Normalize();
    WMVector3 u = WMVector3::Cross(l, r).Normalize();

    m[0][0] = r.x;
    m[1][0] = r.y;
    m[2][0] = r.z;
    m[3][0] = -WMVector3::Dot(r, eye);

    m[0][1] = u.x;
    m[1][1] = u.y;
    m[2][1] = u.z;
    m[3][1] = -WMVector3::Dot(u, eye);

    m[0][2] = l.x;
    m[1][2] = l.y;
    m[2][2] = l.z;
    m[3][2] = -WMVector3::Dot(l, eye);

    return *this;
}

const WMMatrix4& WMMatrix4::Projection(float fov, float aspect, float nearZ, float farZ)
{
    fov = WildMini::Math::DegToRad(fov) * 0.5f;
    float sy = cosf(fov) / sinf(fov);
    float sx = sy / aspect;
    m[0][0] = sx;
    m[1][1] = sy;
    m[2][2] = farZ / (farZ - nearZ);
    m[3][2] = -farZ * nearZ / (farZ - nearZ);

    m[2][3] = 1.0f;
    m[3][3] = 0.0f;

    return *this;
}

const WMMatrix4& WMMatrix4::Viewport(float x, float y, float w, float h, float minZ, float maxZ)
{
    return *this;
}

float WMMatrix4::Determinant()
{
    return
        (_14 * _23 * _32 * _41) - (_13 * _24 * _32 * _41) - (_14 * _22 * _33 * _41) + (_12 * _24 * _33 * _41) + (_13 * _22 * _34 * _41) - (_12 * _23 * _34 * _41) -
        (_14 * _23 * _31 * _42) + (_13 * _24 * _31 * _42) + (_14 * _21 * _33 * _42) - (_11 * _24 * _33 * _42) - (_13 * _21 * _34 * _42) + (_11 * _23 * _34 * _42) +
        (_14 * _22 * _31 * _43) - (_12 * _24 * _31 * _43) - (_14 * _21 * _32 * _43) + (_11 * _24 * _32 * _43) + (_12 * _21 * _34 * _43) - (_11 * _22 * _34 * _43) -
        (_13 * _22 * _31 * _44) + (_12 * _23 * _31 * _44) + (_13 * _21 * _32 * _44) - (_11 * _23 * _32 * _44) - (_12 * _21 * _33 * _44) + (_11 * _22 * _33 * _44);
}

WMMatrix4 WMMatrix4::Adjoint()
{
    WMMatrix4 adj;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            adj.m[y][x] = Cofactor(y, x);
        }
    }
    return adj;
}

float WMMatrix4::Cofactor(int _y, int _x)
{
    float cof = Minor(_y, _x);
    if (((_y + _x) % 2) == 1)
    {
        cof *= -1.0f;
    }

    return cof;
}

float WMMatrix4::Minor(int _y, int _x)
{
    float min = 0.0f;
    WMMatrix3 mat;
    int i = 0;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (y != _y && x != _x)
            {
                mat.m[i / 3][i % 3] = m[y][x];
                ++i;
            }
        }
    }

    min = (mat._11 * mat._22 * mat._33)
        + (mat._12 * mat._23 * mat._31)
        + (mat._13 * mat._21 * mat._32)
        - (mat._13 * mat._22 * mat._31)
        - (mat._12 * mat._21 * mat._33)
        - (mat._11 * mat._23 * mat._32);

    return min;
}

bool WMMatrix4::operator==(const WMMatrix4& value) const
{
    for (int i = 0; i < 16; i++)
    {
        if (v[i] != value.v[i])
        {
            return false;
        }
    }

    return true;
}

bool WMMatrix4::operator!=(const WMMatrix4& value) const
{
    return !(*this == value);
}

WMMatrix4 WMMatrix4::operator+(const WMMatrix4& value) const
{
    WMMatrix4 add(*this);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            add.m[y][x] += value.m[y][x];
        }
    }

    return add;
}

WMMatrix4 WMMatrix4::operator-(const WMMatrix4& value) const
{
    WMMatrix4 sub(*this);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            sub.m[y][x] -= value.m[y][x];
        }
    }

    return sub;
}

WMMatrix4 WMMatrix4::operator*(const WMMatrix4& value) const
{
    WMMatrix4 mul;
    mul._11 = _11 * value._11 + _12 * value._21 + _13 * value._31 + _14 * value._41;
    mul._12 = _11 * value._12 + _12 * value._22 + _13 * value._32 + _14 * value._42;
    mul._13 = _11 * value._13 + _12 * value._23 + _13 * value._33 + _14 * value._43;
    mul._14 = _11 * value._14 + _12 * value._24 + _13 * value._34 + _14 * value._44;

    mul._21 = _21 * value._11 + _22 * value._21 + _23 * value._31 + _24 * value._41;
    mul._22 = _21 * value._12 + _22 * value._22 + _23 * value._32 + _24 * value._42;
    mul._23 = _21 * value._13 + _22 * value._23 + _23 * value._33 + _24 * value._43;
    mul._24 = _21 * value._14 + _22 * value._24 + _23 * value._34 + _24 * value._44;

    mul._31 = _31 * value._11 + _32 * value._21 + _33 * value._31 + _34 * value._41;
    mul._32 = _31 * value._12 + _32 * value._22 + _33 * value._32 + _34 * value._42;
    mul._33 = _31 * value._13 + _32 * value._23 + _33 * value._33 + _34 * value._43;
    mul._34 = _31 * value._14 + _32 * value._24 + _33 * value._34 + _34 * value._44;

    mul._41 = _41 * value._11 + _42 * value._21 + _43 * value._31 + _44 * value._41;
    mul._42 = _41 * value._12 + _42 * value._22 + _43 * value._32 + _44 * value._42;
    mul._43 = _41 * value._13 + _42 * value._23 + _43 * value._33 + _44 * value._43;
    mul._44 = _41 * value._14 + _42 * value._24 + _43 * value._34 + _44 * value._44;

    return mul;
}

WMMatrix4 WMMatrix4::operator*(const float& value) const
{
    WMMatrix4 mul(*this);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            mul.m[y][x] *= value;
        }
    }

    return mul;
}
