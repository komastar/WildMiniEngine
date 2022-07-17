//
//  File:   WMMesh.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Object/WMObject.h"
#include "Graphics/WMGPUBuffer.h"
#include "Graphics/Geometry/WMVertex.h"

namespace WildMini::Graphics::Geometry
{
    struct WMMesh
    {
        std::vector<WildMini::Graphics::Geometry::WMVertex> vertices;
        WildMini::Object::WMObject<WildMini::Graphics::WMGPUBuffer> vertexBuffer;
    };
}
