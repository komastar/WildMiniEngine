#include "pch.h"

Matrix2 Matrix2::Inversed(Matrix2& m)
{
    Matrix2 inversed(m);
    inversed.Inverse();

    return inversed;
}

Matrix2 Matrix2::Identity()
{
    static Matrix2 identity = {
        1.0f, 0.0f
        , 0.0f, 1.0f
    };

    return identity;
}

Matrix2::Matrix2()
{
    for (int i = 0; i < 4; i++)
    {
        v[i] = 0.0f;
    }
}

Matrix2::Matrix2(float _11, float _12, float _21, float _22)
{
    this->_11 = _11;
    this->_12 = _12;

    this->_21 = _21;
    this->_21 = _22;
}

Matrix2::Matrix2(const Matrix3& m)
{
    _11 = m._11;
    _12 = m._12;

    _21 = m._21;
    _22 = m._22;
}

Matrix2::Matrix2(const Matrix4& m)
{
    _11 = m._11;
    _12 = m._12;

    _21 = m._21;
    _22 = m._22;
}

void Matrix2::Transpose()
{
    float t = _12;
    _12 = _21;
    _21 = t;
}

void Matrix2::Inverse()
{
    Matrix2 inv;
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
}

void Matrix2::Scale(float x, float y)
{
    _11 = x;
    _22 = y;
}

void Matrix2::Scale(const Vector2& v)
{
    _11 = v.x;
    _22 = v.y;
}

float Matrix2::Determinant()
{
    return (_11 * _22) - (_12 * _21);
}

bool Matrix2::operator==(const Matrix2& value) const
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

bool Matrix2::operator!=(const Matrix2& value) const
{
    return !(*this == value);
}

Matrix2 Matrix2::operator+(const Matrix2& value) const
{
    Matrix2 add(*this);
    for (int y = 0; y < 2; y++)
    {
        for (int x = 0; x < 2; x++)
        {
            add.m[y][x] += value.m[y][x];
        }
    }

    return add;
}

Matrix2 Matrix2::operator-(const Matrix2& value) const
{
    Matrix2 sub(*this);
    for (int y = 0; y < 2; y++)
    {
        for (int x = 0; x < 2; x++)
        {
            sub.m[y][x] -= value.m[y][x];
        }
    }

    return sub;
}

Matrix2 Matrix2::operator*(const Matrix2& value) const
{
    Matrix2 mul;
    mul._11 = _11 * value._11 + _12 * value._21;
    mul._12 = _11 * value._12 + _12 * value._22;
    mul._21 = _21 * value._11 + _22 * value._21;
    mul._22 = _21 * value._12 + _22 * value._22;

    return mul;
}

Matrix2 Matrix2::operator*(const float& value) const
{
    Matrix2 mul(*this);
    for (int y = 0; y < 2; y++)
    {
        for (int x = 0; x < 2; x++)
        {
            mul.m[y][x] *= value;
        }
    }

    return mul;
}