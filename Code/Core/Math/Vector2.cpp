#include "Vector2.h"

using namespace Core::Math;

const Vector2 Vector2::one = Vector2(1.0f, 1.0f);
const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::left = Vector2(-1.0f, 0.0f);
const Vector2 Vector2::up = Vector2(0.0f, 1.0f);
const Vector2 Vector2::right = Vector2(1.0f, 0.0f);
const Vector2 Vector2::down = Vector2(0.0f, -1.0f);

Vector2 Vector2::Normalized(Vector2 v)
{
    Vector2 normalized(v);
    normalized.Normalize();

    return normalized;
}

float Vector2::Dot(const Vector2& v1, const Vector2& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

const Vector2& Vector2::Left()
{
    static const auto left = Vector2(-1.0f, 0.0f);
    return left;
}

const Vector2& Vector2::Right()
{
    static const auto right = Vector2(1.0f, 0.0f);
    return right;
}

const Vector2& Vector2::Up()
{
    static const auto up = Vector2(0.0f, 1.0f);
    return up;
}

const Vector2& Vector2::Down()
{
    static const auto down = Vector2(0.0f, -1.0f);
    return down;
}

Vector2::Vector2()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2::Vector2(const Vector3& v)
{
    x = v.x;
    y = v.y;
}

Vector2::Vector2(Vector4 v)
{
    x = v.x;
    y = v.y;
}

Vector2::Vector2(float _x, float _y)
{
    x = _x;
    y = _y;
}

Vector2::Vector2(float xy)
{
    x = xy;
    y = xy;
}

float Vector2::Length()
{
    return sqrtf(x * x + y * y);
}

float Vector2::LengthSq()
{
    return x * x + y * y;
}

void Vector2::Normalize()
{
    float inv = 1.0f / sqrtf(x * x + y * y);
    x *= inv;
    y *= inv;
}

bool Vector2::operator==(const Vector2& value) const
{
    return x == value.x && y == value.y;
}

bool Vector2::operator!=(const Vector2& value) const
{
    return !(*this == value);
}

Vector2 Vector2::operator+(const Vector2& value) const
{
    return Vector2(x + value.x, y + value.y);
}

Vector2 Vector2::operator-(const Vector2& value) const
{
    return Vector2(x - value.x, y - value.y);
}

Vector2 Vector2::operator*(const float& value) const
{
    return Vector2(x * value, y * value);
}

const Vector2& Vector2::operator+=(const float& value)
{
    this->x = this->x + value;
    this->y = this->y + value;
    return *this;
}

const Vector2& Vector2::operator-=(const float& value)
{
    this->x = this->x - value;
    this->y = this->y - value;
    return *this;
}

const Vector2& Vector2::operator*=(const float& value)
{
    this->x = this->x * value;
    this->y = this->y * value;
    return *this;
}

const Vector2& Vector2::operator/=(const float& value)
{
    float inv = 1.0f / value;
    this->x = this->x / inv;
    this->y = this->y / inv;
    return *this;
}

const Vector2& Vector2::operator+=(const Vector2& value)
{
    this->x = this->x + value.x;
    this->y = this->y + value.y;
    return *this;
}

const Vector2& Vector2::operator-=(const Vector2& value)
{
    this->x = this->x - value.x;
    this->y = this->y - value.y;
    return *this;
}

const Vector2& Vector2::operator*=(const Vector2& value)
{
    this->x = this->x * value.x;
    this->y = this->y * value.y;
    return *this;
}

const Vector2& Vector2::operator/=(const Vector2& value)
{
    this->x = this->x / value.x;
    this->y = this->y / value.y;
    return *this;
}

Vector2 Vector2::operator*(const Matrix2& value) const
{
    return Vector2((x * value._11 + y * value._21), (x * value._12 + y * value._22));
}

Vector2 Vector2::operator/(const float& value) const
{
    float inv = 1.0f / value;
    return Vector2(x * inv, y * inv);
}
