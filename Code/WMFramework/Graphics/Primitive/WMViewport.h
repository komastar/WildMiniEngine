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
                float nearDepth;
                float farDepth;
            };

            struct 
            {
                float x;
                float y;
                float width;
                float height;
                float nearDepth;
                float farDepth;
            };

            float c[6];
        };

    public:
        WMViewport();
        WMViewport(WMRect _rect, float _near, float _far);
        WMViewport(float _x, float _y, float _width, float _height, float _near, float _far);
    };
}