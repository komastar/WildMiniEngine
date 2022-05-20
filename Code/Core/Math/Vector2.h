#pragma once
#include "Core.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix2.h"

namespace Core::Math
{
    class Vector3;
    class Vector4;
    class Matrix2;
    class Vector2
    {
    public:
        union
        {
            struct
            {
                float x;
                float y;
            };
            float c[2];
        };

    public:
        static Vector2 Normalized(Vector2 v);
        static float Dot(const Vector2& v1, const Vector2& v2);

        const static Vector2& Left();
        const static Vector2& Right();
        const static Vector2& Up();
        const static Vector2& Down();

    public:
        Vector2();
        Vector2(const Vector3& v);
        Vector2(Vector4 v);
        Vector2(float _x, float _y);
        Vector2(float xy);

    public:
        float Length();
        float LengthSq();
        void Normalize();

    public:
        bool operator==(const Vector2& value) const;
        bool operator!=(const Vector2& value) const;
        Vector2 operator+(const Vector2& value) const;
        Vector2 operator-(const Vector2& value) const;
        Vector2 operator*(const float& value) const;
        Vector2 operator*(const Matrix2& value) const;
        Vector2 operator/(const float& value) const;
    };
}
