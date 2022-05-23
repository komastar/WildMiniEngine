#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace Core::Math
{
    class Vector2;
    class Vector3;
    class Matrix4;
    class Vector4
    {
    public:
        union
        {
            struct
            {
                float x;
                float y;
                float z;
                float w;
            };
            float c[4];
        };

    public:
        static Vector4 Normalized(Vector4 v);
        static float Dot(const Vector4& v1, const Vector4& v2);

        static const Vector4& Forward();
        static const Vector4& Backward();
        static const Vector4& Left();
        static const Vector4& Right();
        static const Vector4& Up();
        static const Vector4& Down();

    public:
        Vector4();
        Vector4(Vector2 v);
        Vector4(Vector3 v);
        Vector4(float _x, float _y);
        Vector4(float _x, float _y, float _z);
        Vector4(float _x, float _y, float _z, float _w);
        Vector4(float xyzw);

    public:
        float Length();
        float LengthSq();
        void Normalize();

    public:
        bool operator==(const Vector4& value) const;
        bool operator!=(const Vector4& value) const;
        Vector4 operator+(const Vector4& value) const;
        Vector4 operator-(const Vector4& value) const;
        Vector4 operator*(const float& value) const;
        Vector4 operator*(const Matrix4& value) const;
        Vector4 operator/(const float& value) const;

    public:
        static const Vector4 one;
        static const Vector4 zero;
        static const Vector4 left;
        static const Vector4 up;
        static const Vector4 right;
        static const Vector4 down;
        static const Vector4 back;
        static const Vector4 forward;
    };
}
