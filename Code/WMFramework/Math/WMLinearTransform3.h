//
//  File:   WMLinearTransform3.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMMatrix3.h"
#include "WMVector3.h"

namespace WildMini::Math
{
    class WMVector3;
    class WMMatrix3;
    class WMLinearTransform3
    {
    public:
        WMMatrix3 m;

    public:
        WMLinearTransform3();
        WMLinearTransform3(const WMMatrix3& _m);

    public:
        WMLinearTransform3 Scale(const float& x, const float& y, const float& z);
        WMLinearTransform3 Scale(const WMVector3& v);
        WMLinearTransform3 RotateX(float r);
        WMLinearTransform3 RotateY(float r);
        WMLinearTransform3 RotateZ(float r);
        WMLinearTransform3 Rotate(const WMVector3& axis, float r);
        WMLinearTransform3 Multiply(const WMMatrix3& _m);

    public:
        bool operator==(const WMLinearTransform3& lt) const;
        bool operator!=(const WMLinearTransform3& lt) const;
    };
}
