#include "Math.h"

using namespace Core::Math;

Matrix4 Matrix4::Inversed(Matrix4& m)
{
    Matrix4 inversed(m);
    inversed.Inverse();

    return inversed;
}

Matrix4 Matrix4::Identity()
{
    static Matrix4 mat = {
        1.0f, 0.0f, 0.0f, 0.0f
        , 0.0f, 1.0f, 0.0f, 0.0f
        , 0.0f, 0.0f, 1.0f, 0.0f
        , 0.0f, 0.0f, 0.0f, 1.0f
    };

    return mat;
}

Matrix4 Matrix4::Transposed(Matrix4& m)
{
    Matrix4 transposed(m);
    transposed.Transpose();

    return transposed;
}

Matrix4::Matrix4()
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

Matrix4::Matrix4(float _11, float _12, float _13, float _14
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

Matrix4::Matrix4(const Matrix2& m)
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

Matrix4::Matrix4(const Matrix3& m)
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

void Matrix4::Transpose()
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

void Matrix4::Inverse()
{
    Matrix4 inv;
    float d = Determinant();
    if (0.0f < fabsf(d))
    {
        inv = Adjoint() * (1.0f / d);
        std::memcpy(m, inv.m, 16);
    }
}

const Matrix4& Matrix4::View(const Vector3& eye, const Vector3& lookat, const Vector3& up)
{
    Vector3 l = (lookat - eye).Normalize();
    Vector3 r = Vector3::Cross(up, l).Normalize();
    Vector3 u = Vector3::Cross(l, r).Normalize();

    m[0][0] = r.x;
    m[1][0] = r.y;
    m[2][0] = r.z;
    m[3][0] = -Vector3::Dot(r, eye);

    m[0][1] = u.x;
    m[1][1] = u.y;
    m[2][1] = u.z;
    m[3][1] = -Vector3::Dot(u, eye);

    m[0][2] = l.x;
    m[1][2] = l.y;
    m[2][2] = l.z;
    m[3][2] = -Vector3::Dot(l, eye);

    return *this;
}

const Matrix4& Matrix4::Projection(float fov, float aspect, float nearZ, float farZ)
{
    fov = DegToRad(fov) * 0.5f;
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

const Matrix4& Matrix4::Viewport(float x, float y, float w, float h, float minZ, float maxZ)
{
    return *this;
}

float Matrix4::Determinant()
{
    float d = 0.0f;
    for (int y = 0; y < 4; y++)
    {
        float cof = Cofactor(y, 0);
        d += m[y][0] * cof;
    }

    return d;
}

Matrix4 Matrix4::Adjoint()
{
    Matrix4 adj;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            adj.m[y][x] = Cofactor(y, x);
        }
    }
    return adj;
}

float Matrix4::Cofactor(int _y, int _x)
{
    float cof = Minor(_y, _x);
    if (((_y + _x) % 2) == 1)
    {
        cof *= -1.0f;
    }

    return cof;
}

float Matrix4::Minor(int _y, int _x)
{
    float min = 0.0f;
    Matrix3 mat;
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

bool Matrix4::operator==(const Matrix4& value) const
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

bool Matrix4::operator!=(const Matrix4& value) const
{
    return !(*this == value);
}

Matrix4 Matrix4::operator+(const Matrix4& value) const
{
    Matrix4 add(*this);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            add.m[y][x] += value.m[y][x];
        }
    }

    return add;
}

Matrix4 Matrix4::operator-(const Matrix4& value) const
{
    Matrix4 sub(*this);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            sub.m[y][x] -= value.m[y][x];
        }
    }

    return sub;
}

Matrix4 Matrix4::operator*(const Matrix4& value) const
{
    Matrix4 mul;
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

Matrix4 Matrix4::operator*(const float& value) const
{
    Matrix4 mul(*this);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            mul.m[y][x] *= value;
        }
    }

    return mul;
}