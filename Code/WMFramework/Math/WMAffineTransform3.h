//
//  File:   WMAffineTransform3.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMVector3.h"
#include "WMMatrix3.h"
#include "WMLinearTransform3.h"

namespace WildMini::Math
{
    class WMVector3;
    class WMMatrix3;
    class WMLinearTransform3;
    class WMAffineTransform3
    {
    public:
        WMMatrix3 m;
        WMVector3 v;

    public:
        WMAffineTransform3();
        WMAffineTransform3(const WMMatrix3& _m);

    public:
        WMAffineTransform3 Translate(float x, float y, float z);
        WMAffineTransform3 Translate(const WMVector3& _v);
        WMAffineTransform3 Multiply(const WMAffineTransform3& at);
        WMAffineTransform3 Multiply(const WMLinearTransform3& lt);

    public:
        bool operator==(const WMAffineTransform3& at) const;
        bool operator!=(const WMAffineTransform3& at) const;
    };
}
