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
#include "WMContainer.h"

namespace WildMini
{
    struct WMMesh
    {
        Vector<WMVertex> vertices;
        Vector<uint32_t> indices;
        WMSharedPtr<WMGPUBuffer> vertexBuffer;
        WMSharedPtr<WMGPUBuffer> indexBuffer;

        WMMesh()
            : vertexBuffer(nullptr)
            , indexBuffer(nullptr)
        {
        }

        virtual ~WMMesh()
        {
            vertexBuffer = nullptr;
            indexBuffer = nullptr;
        }
    };
}
