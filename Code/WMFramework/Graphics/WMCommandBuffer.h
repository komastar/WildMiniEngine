//
//  File:   WMCommandBuffer.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Object/WMObject.h"
#include "Graphics/WMRenderCommandEncoder.h"
#include "Graphics/WMRenderPipeline.h"

namespace WildMini::Graphics
{
    class WM_API WMCommandBuffer : public WildMini::Object::WMRefCounter
    {
    public:
        virtual WildMini::Object::WMObject<WMRenderCommandEncoder> CreateRenderCommandEncoder(WMRenderPipeline* renderPipeline) = 0;
        virtual void Commit() = 0;
    };
}
