//
//  File:   WMGeometryFactory.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Graphics/WMGraphicsDevice.h"
#include "Graphics/Primitive/WMColor.h"
#include "Graphics/Geometry/WMMesh.h"

namespace WildMini
{
    class WMGeometryFactory
    {
    public:
        static WMMesh* MakeDefaultBox(WMGraphicsDevice* device);
        static WMMesh* MakeBox(WMGraphicsDevice* device, float size);
        static WMMesh* MakeQuad(WMGraphicsDevice* device, float size, const WMColor& color);
        static WMMesh* MakePlane(WMGraphicsDevice* device, float size, const WMColor& color);
    };
}
