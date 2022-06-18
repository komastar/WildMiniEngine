//
//  File:   WMGraphicsDevice.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Object/WMObject.h"
#include "WMCommandQueue.h"
#include "WMGPUBuffer.h"
#include "WMTexture.h"

namespace WildMini::Graphics
{
    class WM_API WMGraphicsDevice : public WildMini::Object::WMRefCounter
    {
    public:
        static WMGraphicsDevice* CreateGraphicsDevice();

    public:
        virtual WildMini::Object::WMObject<WildMini::Graphics::WMCommandQueue> CreateCommandQueue() = 0;
        virtual WildMini::Object::WMObject<WildMini::Graphics::WMGPUBuffer> CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode) = 0;
        virtual WildMini::Object::WMObject<WildMini::Graphics::WMTexture> CreateTexture(const WMTexture::Desc& desc) = 0;
    };
}
