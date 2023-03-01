//
//  File:   WMCommandBuffer.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMSharedPtr.h"
#include "Graphics/WMRenderCommandEncoder.h"
#include "Graphics/WMRenderPipeline.h"

namespace WildMini
{
    class WM_API WMCommandBuffer : public WMRefCounter
    {
    public:
        virtual WMSharedPtr<WMRenderCommandEncoder> CreateRenderCommandEncoder(WMRenderPipeline* renderPipeline) = 0;
        virtual void Commit() = 0;
    };
}
