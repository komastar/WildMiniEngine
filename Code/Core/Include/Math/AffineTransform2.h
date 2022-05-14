#pragma once
class Matrix2;
class Matrix3;
class Vector2;
class LinearTransform2;

class AffineTransform2
{
public:
    Matrix2 m;
    Vector2 v;

public:
    AffineTransform2();
    AffineTransform2(const class Matrix3& _m);

public:
    AffineTransform2 Translate(float x, float y);
    AffineTransform2 Translate(const Vector2& _v);
    AffineTransform2 Multiply(const AffineTransform2& at);
    AffineTransform2 Multiply(const class LinearTransform2& lt);

public:
    bool operator==(const AffineTransform2& at) const;
    bool operator!=(const AffineTransform2& at) const;
};
