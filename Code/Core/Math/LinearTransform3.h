#pragma once
#include "Core.h"
#include "Matrix3.h"
#include "Vector3.h"

namespace Core::Math
{
    class Vector3;
    class Matrix3;
    class LinearTransform3
    {
    public:
        Matrix3 m;

    public:
        LinearTransform3();
        LinearTransform3(const Matrix3& _m);

    public:
        LinearTransform3 Scale(const float& x, const float& y, const float& z);
        LinearTransform3 Scale(const Vector3& v);
        LinearTransform3 RotateX(float r);
        LinearTransform3 RotateY(float r);
        LinearTransform3 RotateZ(float r);
        LinearTransform3 Rotate(const Vector3& axis, float r);
        LinearTransform3 Multiply(const Matrix3& _m);

    public:
        bool operator==(const LinearTransform3& lt) const;
        bool operator!=(const LinearTransform3& lt) const;
    };
}