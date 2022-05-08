#pragma once
class Vector4;
class Matrix2;
class Matrix3;

class Matrix4
{
public:
    union
    {
        Vector4 r[4];
        struct
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float m[4][4];
        float v[16];
    };

public:
    static Matrix4 Inversed(Matrix4& m);
    static Matrix4 Identity();
    static Matrix4 Transposed(Matrix4& m);

public:
    Matrix4();
    Matrix4(float _11, float _12, float _13, float _14
        , float _21, float _22, float _23, float _24
        , float _31, float _32, float _33, float _34
        , float _41, float _42, float _43, float _44);
    Matrix4(const Matrix2& m);
    Matrix4(const Matrix3& m);

public:
    void Transpose();
    void Inverse();

private:
    float Determinant();
    Matrix4 Adjoint();
    float Cofactor(int y, int x);
    float Minor(int y, int x);

public:
    bool operator==(const Matrix4& value) const;
    bool operator!=(const Matrix4& value) const;
    Matrix4 operator+(const Matrix4& value) const;
    Matrix4 operator-(const Matrix4& value) const;
    Matrix4 operator*(const Matrix4& value) const;
    Matrix4 operator*(const float& value) const;
};
