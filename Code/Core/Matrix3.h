#pragma once
class Vector3;
class Matrix2;
class Matrix4;

class Matrix3
{
public:
    union
    {
        Vector3 r[3];
        struct
        {
            float _11, _12, _13;
            float _21, _22, _23;
            float _31, _32, _33;
        };
        float m[3][3];
        float v[9];
    };

public:
    static Matrix3 Inversed(Matrix3& m);
    static Matrix3 Identity();
    static Matrix3 Transposed(Matrix3& m);

public:
    Matrix3();
    Matrix3(float _11, float _12, float _13
        , float _21, float _22, float _23
        , float _31, float _32, float _33);
    Matrix3(const Matrix2& m);
    Matrix3(const Matrix4& m);

public:
    void Transpose();
    void Inverse();

private:
    float Determinant();
    Matrix3 Adjoint();
    float Cofactor(int y, int x);
    float Minor(int y, int x);

public:
    bool operator==(const Matrix3& value) const;
    bool operator!=(const Matrix3& value) const;
    Matrix3 operator+(const Matrix3& value) const;
    Matrix3 operator-(const Matrix3& value) const;
    Matrix3 operator*(const Matrix3& value) const;
    Matrix3 operator*(const float& value) const;
};
