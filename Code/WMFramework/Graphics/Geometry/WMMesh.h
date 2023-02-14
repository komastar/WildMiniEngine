//
//  File:   WMMesh.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMSharedPtr.h"
#include "Graphics/WMGPUBuffer.h"
#include "Graphics/Geometry/WMVertex.h"

namespace WildMini::Graphics::Geometry
{
    struct WMMesh
    {
        std::vector<WildMini::Graphics::Geometry::WMVertex> vertices;
        std::vector<uint32_t> indices;
        WildMini::WMSharedPtr<WildMini::Graphics::WMGPUBuffer> vertexBuffer;
        WildMini::WMSharedPtr<WildMini::Graphics::WMGPUBuffer> indexBuffer;

        WMMesh()
            : vertexBuffer(nullptr)
            , indexBuffer(nullptr)
        {
        }
    };
}
