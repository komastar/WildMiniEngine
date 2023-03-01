//
//  File:   WMLinearTransform2.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMVector2.h"
#include "WMMatrix2.h"

namespace WildMini
{
    class WMVector2;
    class WMMatrix2;
    class WMLinearTransform2
    {
    public:
        WMMatrix2 m;

    public:
        WMLinearTransform2();
        WMLinearTransform2(const WMMatrix2& _m);

    public:
        WMLinearTransform2 Scale(const float& x, const float& y);
        WMLinearTransform2 Scale(const WMVector2& v);
        WMLinearTransform2 Rotate(const float r);
        WMLinearTransform2 Multiply(const WMMatrix2& _m);

    public:
        bool operator==(const WMLinearTransform2& lt) const;
        bool operator!=(const WMLinearTransform2& lt) const;
    };
}
