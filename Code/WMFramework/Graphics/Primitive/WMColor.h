//
//  File:   WMColor.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"

namespace WildMini::Graphics::Primitive
{
    class WMColor
    {
    public:
        union
        {
            float c[4];
            struct 
            {
                float r;
                float g;
                float b;
                float a;
            };
        };

    public:
        WMColor();
        WMColor(float rgba);
        WMColor(float r, float g, float b, float a = 1.0f);

    public:
        WMColor Clamp();

    public:
        WMColor operator+(const WMColor& color) const;
        WMColor operator-(const WMColor& color) const;
        WMColor operator*(float v) const;
        WMColor operator/(float v) const;

        bool operator==(const WMColor& color) const;
        bool operator!=(const WMColor& color) const;

    public:
        static const WMColor transparent;
        static const WMColor white;
        static const WMColor black;
        static const WMColor red;
        static const WMColor green;
        static const WMColor blue;
        static const WMColor cyan;
        static const WMColor magenta;
        static const WMColor yellow;
    };
}
