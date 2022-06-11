#pragma once
#include "Math/WMVector2.h"

using Vector2 = WildMini::Math::WMVector2;

namespace WildMini::Graphics::Primitive
{
    class WMQuad
    {
    public:
        union
        {
            struct
            {
                Vector2 lt;
                Vector2 rt;
                Vector2 lb;
                Vector2 rb;
            };

            Vector2 c[4];
        };

    public:
        WMQuad();
        WMQuad(const WMQuad& quad) = default;
        WMQuad(WMQuad&& quad) = default;
        WMQuad(Vector2 _lt, Vector2 _rt, Vector2 _lb, Vector2 _rb);

    public:
        static const WMQuad zero;
        static const WMQuad one;
        static const WMQuad inf;
    };
}
