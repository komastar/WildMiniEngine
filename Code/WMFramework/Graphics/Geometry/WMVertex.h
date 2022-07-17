#pragma once
#include "Math/WMVector3.h"
#include "Graphics/Primitive/WMColor.h"

namespace WildMini::Graphics::Geometry
{
    struct WMVertex
    {
        WildMini::Math::WMVector3 p;
        WildMini::Math::WMVector3 n;
        WildMini::Graphics::Primitive::WMColor c;
    };
}
