#pragma once
#include "Core.h"

namespace Core::Math
{
    class Vector3;
    class Matrix2;
    class Matrix3;
    class Matrix4
    {
    public:
        union
        {
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
        Matrix4 Inverse();
        const Matrix4& View(const Vector3& eye, const Vector3& lookat, const Vector3& up);
        const Matrix4& Projection(float fov, float aspect, float nearZ, float farZ);
        const Matrix4& Viewport(float x, float y, float w, float h, float minZ, float maxZ);

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
}
