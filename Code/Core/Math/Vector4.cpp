#include "Vector4.h"

using namespace Core::Math;

Vector4 Vector4::Normalized(Vector4 v)
{
    Vector4 normalized(v);
    normalized.Normalize();

return normalized;
}

float Vector4::Dot(const Vector4& v1, const Vector4& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

const Vector4& Vector4::Forward()
{
    static const auto forward = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
    return forward;
}

const Vector4& Vector4::Backward()
{
    static const auto backward = Vector4(0.0f, 0.0f, -1.0f, 1.0f);
    return backward;
}

const Vector4& Vector4::Left()
{
    static const auto left = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
    return left;
}

const Vector4& Vector4::Right()
{
    static const auto right = Vector4(-1.0f, 0.0f, 0.0f, 1.0f);
    return right;
}

const Vector4& Vector4::Up()
{
    static const auto up = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
    return up;
}

const Vector4& Vector4::Down()
{
    static const auto down = Vector4(0.0f, -1.0f, 0.0f, 1.0f);
    return down;
}

Vector4::Vector4()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}

Vector4::Vector4(Vector2 v)
{
    x = v.x;
    y = v.y;
    z = 0.0f;
    w = 0.0f;
}

Vector4::Vector4(Vector3 v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = 0.0f;
}

Vector4::Vector4(float _x, float _y)
{
    x = _x;
    y = _y;
    z = 0.0f;
    w = 0.0f;
}

Vector4::Vector4(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
    w = 0.0f;
}

Vector4::Vector4(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

Vector4::Vector4(float xyzw)
{
    x = xyzw;
    y = xyzw;
    z = xyzw;
    w = xyzw;
}

float Vector4::Length()
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

float Vector4::LengthSq()
{
    return x * x + y * y + z * z + w * w;
}

void Vector4::Normalize()
{
    float inv = 1.0f / sqrtf(x * x + y * y + z * z + w * w);
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
}

bool Vector4::operator==(const Vector4& value) const
{
    return x == value.x && y == value.y && z == value.z && w == value.w;
}

bool Vector4::operator!=(const Vector4& value) const
{
    return !(*this == value);
}

Vector4 Vector4::operator+(const Vector4& value) const
{
    return Vector4(x + value.x, y + value.y, z + value.z, w + value.w);
}

Vector4 Vector4::operator-(const Vector4& value) const
{
    return Vector4(x - value.x, y - value.y, z - value.z, w - value.w);
}

Vector4 Vector4::operator*(const float& value) const
{
    return Vector4(x * value, y * value, z * value, w * value);
}

Vector4 Vector4::operator*(const Matrix4& value) const
{
    return Vector4(
        x * value._11 + y * value._21 + z * value._31 + w * value._41,
        x * value._12 + y * value._22 + z * value._32 + w * value._42,
        x * value._13 + y * value._23 + z * value._33 + w * value._43,
        x * value._14 + y * value._24 + z * value._34 + w * value._44
    );
}

Vector4 Vector4::operator/(const float& value) const
{
    float inv = 1.0f / value;
    return Vector4(x * inv, y * inv, z * inv, w * inv);
}
