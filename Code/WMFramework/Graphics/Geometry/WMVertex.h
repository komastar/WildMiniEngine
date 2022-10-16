//
//  File:   WMVertex.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "Math/WMVector3.h"
#include "Graphics/Primitive/WMColor.h"

namespace WildMini::Graphics::Geometry
{
    struct WMVertex
    {
        WildMini::Math::WMVector3 p;
        WildMini::Math::WMVector2 t;
        WildMini::Graphics::Primitive::WMColor c;
    };
}
