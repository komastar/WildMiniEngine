#pragma once
class Matrix3;
class Matrix4;
class Vector2;

class Matrix2
{
public:
    union
    {
        Vector2 r[2];
        struct
        {
            float _11, _12;
            float _21, _22;
        };
        float m[2][2];
        float v[4];
    };

public:
    static Matrix2 Inversed(Matrix2& m);
    static Matrix2 Identity();

public:
    Matrix2();
    Matrix2(float _11, float _12, float _21, float _22);
    Matrix2(const Matrix3& m);
    Matrix2(const Matrix4& m);

public:
    void Transpose();
    void Inverse();

public:
    void Scale(float x, float y);
    void Scale(const Vector2& v);

private:
    float Determinant();

public:
    bool operator==(const Matrix2& value) const;
    bool operator!=(const Matrix2& value) const;
    Matrix2 operator+(const Matrix2& value) const;
    Matrix2 operator-(const Matrix2& value) const;
    Matrix2 operator*(const Matrix2& value) const;
    Matrix2 operator*(const float& value) const;
};
