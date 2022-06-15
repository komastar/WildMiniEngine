//
//  File:   WMRect.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMPoint.h"
#include "WMSize.h"

namespace WildMini::Graphics::Primitive
{
    class WMRect
    {
    public:
        union
        {
            struct
            {
                WMPoint origin;
                WMSize size;
            };
            struct
            {
                float x;
                float y;
                float width;
                float height;
            };
            float c[4];
        };

    public:
        WMRect();
        WMRect(const WMRect& rect) = default;
        WMRect(WMRect&& rect) = default;
        WMRect(float _x, float _y, float _width, float _height);
        WMRect(const WMPoint& _origin, const WMSize& _size);

    public:
        static const WMRect zero;
        static const WMRect one;
        static const WMRect inf;
    };
}
