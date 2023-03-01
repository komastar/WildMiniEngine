//
//  File:   WMVertex.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "Math/WMVector3.h"
#include "Graphics/Primitive/WMColor.h"

namespace WildMini
{
    struct WMVertex
    {
        WMVector3 p;
        WMVector2 t;
        WMColor c;
    };
}
