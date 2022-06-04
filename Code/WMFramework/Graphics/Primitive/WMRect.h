#pragma once
#include "WMQuad.h"

namespace WildMini::Graphics
{
    class WMRect : public WMQuad
    {
    public:
        WMRect();
        WMRect(const WMRect& rect) = default;
        WMRect(WMRect&& rect) = default;
    };
}
