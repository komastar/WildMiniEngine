#include "Math/Math.h"

Vector3 Vector3::Normalized(Vector3 v)
{
    Vector3 normalized(v);
    normalized.Normalize();

    return normalized;
}

float Vector3::Dot(const Vector3& v1, const Vector3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2)
{
    return Vector3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

const Vector3& Vector3::Forward()
{
    static const auto forward = Vector3(0.0f, 0.0f, 1.0f);
    return forward;
}

const Vector3& Vector3::Backward()
{
    static const auto backward = Vector3(0.0f, 0.0f, -1.0f);
    return backward;
}

const Vector3& Vector3::Left()
{
    static const auto left = Vector3(1.0f, 0.0f, 0.0f);
    return left;
}

const Vector3& Vector3::Right()
{
    static const auto right = Vector3(-1.0f, 0.0f, 0.0f);
    return right;
}

const Vector3& Vector3::Up()
{
    static const auto up = Vector3(0.0f, 1.0f, 0.0f);
    return up;
}

const Vector3& Vector3::Down()
{
    static const auto down = Vector3(0.0f, -1.0f, 0.0f);
    return down;
}

Vector3::Vector3()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3::Vector3(Vector2 v)
{
    x = v.x;
    y = v.y;
    z = 0.0f;
}

Vector3::Vector3(Vector4 v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector3::Vector3(float _x, float _y)
{
    x = _x;
    y = _y;
    z = 0.0f;
}

Vector3::Vector3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Vector3::Vector3(float xyz)
{
    x = xyz;
    y = xyz;
    z = xyz;
}

float Vector3::Length()
{
    return sqrtf(x * x + y * y + z * z);
}

float Vector3::LengthSq()
{
    return x * x + y * y + z * z;
}

const Vector3& Vector3::Normalize()
{
    float inv = 1.0f / sqrtf(x * x + y * y + z * z);
    x *= inv;
    y *= inv;
    z *= inv;

    return *this;
}

bool Vector3::operator==(const Vector3& value) const
{
    return x == value.x && y == value.y && z == value.z;
}

bool Vector3::operator!=(const Vector3& value) const
{
    return !(*this == value);
}

Vector3 Vector3::operator+(const Vector3& value) const
{
    return Vector3(x + value.x, y + value.y, z + value.z);
}

Vector3 Vector3::operator-(const Vector3& value) const
{
    return Vector3(x - value.x, y - value.y, z - value.z);
}

Vector3 Vector3::operator*(const float& value) const
{
    return Vector3(x * value, y * value, z * value);
}

Vector3 Vector3::operator*(const Matrix3& value) const
{
    return Vector3(
        x * value._11 + y * value._21 + z * value._31,
        x * value._12 + y * value._22 + z * value._32,
        x * value._13 + y * value._23 + z * value._33
    );
}

Vector3 Vector3::operator/(const float& value) const
{
    float inv = 1.0f / value;
    return Vector3(x * inv, y * inv, z * inv);
}
