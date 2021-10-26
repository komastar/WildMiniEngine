#pragma once
class Matrix3;
class Vector2;
class Vector4;

class Vector3
{
public:
    union
    {
        struct
        {
            float x;
            float y;
            float z;
        };
        float c[3];
    };

public:
    static Vector3 Normalized(Vector3 v);
    static float Dot(const Vector3& v1, const Vector3& v2);
    static Vector3 Cross(const Vector3& v1, const Vector3& v2);

    static const Vector3& Forward();
    static const Vector3& Backward();
    static const Vector3& Left();
    static const Vector3& Right();
    static const Vector3& Up();
    static const Vector3& Down();

public:
    Vector3();
    Vector3(Vector2 v);
    Vector3(Vector4 v);
    Vector3(float _x, float _y);
    Vector3(float _x, float _y, float _z);
    Vector3(float xyz);

public:
    float Length();
    float LengthSq();
    void Normalize();

public:
    bool operator==(const Vector3& value) const;
    bool operator!=(const Vector3& value) const;
    Vector3 operator+(const Vector3& value) const;
    Vector3 operator-(const Vector3& value) const;
    Vector3 operator*(const float& value) const;
    Vector3 operator*(const Matrix3& value) const;
    Vector3 operator/(const float& value) const;
};
