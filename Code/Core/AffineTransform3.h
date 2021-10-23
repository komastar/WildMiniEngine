#pragma once
class Matrix3;
class Vector3;
class LinearTransform3;

class AffineTransform3
{
public:
    Matrix3 m;
    Vector3 v;

public:
    AffineTransform3();
    AffineTransform3(const Matrix3& _m);

public:
    AffineTransform3 Translate(float x, float y, float z);
    AffineTransform3 Translate(const Vector3& _v);
    AffineTransform3 Multiply(const AffineTransform3& at);
    AffineTransform3 Multiply(const LinearTransform3& lt);

public:
    bool operator==(const AffineTransform3& at) const;
    bool operator!=(const AffineTransform3& at) const;
};
