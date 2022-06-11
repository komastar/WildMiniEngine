#pragma once
#include "WMRect.h"

namespace WildMini::Graphics::Primitive
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
                float near;
                float far;
            };

            float c[6];
        };

    public:
        WMViewport();
        WMViewport(WMRect _rect, float _near, float _far);
        WMViewport(float _x, float _y, float _width, float _height, float _near, float _far);
    };
}