#pragma once
#include "Math/WMVector2.h"

namespace WildMini::Graphics
{
    class WMQuad
    {
    public:
        union
        {
            struct
            {
                WildMini::Math::WMVector2 lt;
                WildMini::Math::WMVector2 rt;
                WildMini::Math::WMVector2 lb;
                WildMini::Math::WMVector2 rb;
            };
        };

    public:
        WMQuad();
        WMQuad(const WMQuad& quad) = default;
        WMQuad(WMQuad&& quad) = default;
    };
}
