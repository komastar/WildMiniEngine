#pragma once
#include "Math/WMMath.h"

namespace WildMini::Graphics::Primitive
{
    class WMSize
    {
    public:
        union
        {
            struct
            {
                float width;
                float height;
            };
            float c[2];
        };

    public:
        WMSize();
        WMSize(const WMSize& size) = default;
        WMSize(WMSize&& size) = default;
        WMSize(float _width, float _height);

    public:
        static const WMSize zero;
        static const WMSize one;
        static const WMSize negOne;
        static const WMSize inf;
        static const WMSize negInf;
    };
}
