#pragma once
class Vector2;
class Matrix2;

class LinearTransform2
{
public:
    Matrix2 m;

public:
    LinearTransform2();
    LinearTransform2(const Matrix2& _m);

public:
    LinearTransform2 Scale(const float& x, const float& y);
    LinearTransform2 Scale(const Vector2& v);
    LinearTransform2 Rotate(const float r);
    LinearTransform2 Multiply(const Matrix2& _m);

public:
    bool operator==(const LinearTransform2& lt) const;
    bool operator!=(const LinearTransform2& lt) const;
};
