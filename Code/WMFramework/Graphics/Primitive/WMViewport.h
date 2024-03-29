//
//  File:   WMViewport.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMRect.h"

namespace WildMini
{
    class WMViewport
    {
    public:
        union
        {
            struct
            {
                WMPoint origin;
                WMSize size;
                float nearDepth;
                float farDepth;
            };

            struct 
            {
                float x;
                float y;
                float width;
                float height;
                float nearDepth2;
                float farDepth2;
            };

            float c[6];
        };

    public:
        WMViewport();
        WMViewport(WMRect _rect, float _near, float _far);
        WMViewport(float _x, float _y, float _width, float _height, float _near, float _far);
    };
}
