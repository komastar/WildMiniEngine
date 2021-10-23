#include "pch.h"

Matrix3 Matrix3::Inversed(Matrix3& m)
{
    Matrix3 inversed(m);
    m.Inverse();

    return inversed;
}

Matrix3 Matrix3::Identity()
{
    Matrix3 identity;
    for (int i = 0; i < 3; i++)
    {
        identity.m[i][i] = 1.0f;
    }

    return identity;
}

Matrix3 Matrix3::Transposed(Matrix3& m)
{
    Matrix3 transposed(m);
    m.Transpose();

    return transposed;
}

Matrix3::Matrix3()
{
    for (int i = 0; i < 9; i++)
    {
        v[i] = 0.0f;
    }
}

Matrix3::Matrix3(float _11, float _12, float _13, float _21, float _22, float _23, float _31, float _32, float _33)
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

Matrix3::Matrix3(const Matrix2& m)
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

Matrix3::Matrix3(const Matrix4& m)
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

void Matrix3::Transpose()
{
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            float t = m[y][x];
            m[y][x] = m[x][y];
            m[x][y] = t;
        }
    }
}

void Matrix3::Inverse()
{
    Matrix3 inv;
    float d = Determinant();
    if (0.0f < fabsf(d))
    {
        inv = Adjoint() * (1.0f / d);
    }
}

float Matrix3::Determinant()
{
    float d = 0.0f;
    for (int i = 0; i < 3; i++)
    {
        float cof = Cofactor(i, 0);
        d += m[i][0] * cof;
    }

    return d;
}

Matrix3 Matrix3::Adjoint()
{
    Matrix3 adj;
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

float Matrix3::Cofactor(int y, int x)
{
    float cof = Minor(y, x);
    if (((y + x) % 2) == 1)
    {
        cof *= -1.0f;
    }

    return cof;
}

float Matrix3::Minor(int _y, int _x)
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

bool Matrix3::operator==(const Matrix3& value) const
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

bool Matrix3::operator!=(const Matrix3& value) const
{
    return !(*this == value);
}

Matrix3 Matrix3::operator+(const Matrix3& value) const
{
    Matrix3 add(*this);
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            add.m[y][x] += value.m[y][x];
        }
    }

    return add;
}

Matrix3 Matrix3::operator-(const Matrix3& value) const
{
    Matrix3 sub(*this);
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            sub.m[y][x] -= value.m[y][x];
        }
    }

    return sub;
}

Matrix3 Matrix3::operator*(const Matrix3& value) const
{
    Matrix3 mul;
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

Matrix3 Matrix3::operator*(const float& value) const
{
    Matrix3 mul(*this);
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            mul.m[y][x] *= value;
        }
    }

    return mul;
}