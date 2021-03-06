//
//  File:   WMGeometryFactory.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Graphics/WMGraphicsDevice.h"
#include "WMMesh.h"

namespace WildMini::Graphics::Geometry
{
    class WMGeometryFactory
    {
    public:
        static WMMesh* MakeBox(WildMini::Graphics::WMGraphicsDevice* device);
    };
}