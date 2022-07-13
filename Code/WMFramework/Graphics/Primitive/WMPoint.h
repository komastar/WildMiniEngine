//
//  File:   WMPoint.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "Math/WMMath.h"
#include "Math/WMVector2.h"

namespace WildMini::Graphics::Primitive
{
    class WMPoint
    {
    public:
        union
        {
            struct
            {
                float x;
                float y;
            };

            float c[2];
        };

    public:
        WMPoint();
        WMPoint(const WMPoint& point) = default;
        WMPoint(WMPoint&& point) = default;
        WMPoint(float _x, float _y);
        WMPoint(const WildMini::Math::WMVector2& v);

    public:
        static const WMPoint zero;
        static const WMPoint one;
        static const WMPoint negOne;
        static const WMPoint inf;
        static const WMPoint negInf;
    };
}
