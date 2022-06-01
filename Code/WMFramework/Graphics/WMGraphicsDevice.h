#pragma once
#include "WMFramework.h"
#include "Object/WMObject.h"
#include "WMCommandList.h"
#include "WMCommandQueue.h"
#include "WMSwapChain.h"
#include "WMGPUBuffer.h"
#include "WMTexture.h"

namespace WildMini::Graphics
{
    class WM_API WMGraphicsDevice : public WildMini::Object::WMRefCounter
    {
    public:
        static WMGraphicsDevice* CreateGraphicsDevice();

    public:
        virtual WildMini::Object::WMObject<WMCommandQueue> CreateCommandQueue() = 0;
        virtual WildMini::Object::WMObject<WMCommandList> CreateCommandList() = 0;
        virtual WildMini::Object::WMObject<WMGPUBuffer> CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode) = 0;
        virtual WildMini::Object::WMObject<WMTexture> CreateTexture(const WMTexture::Desc& desc) = 0;
    };
}
