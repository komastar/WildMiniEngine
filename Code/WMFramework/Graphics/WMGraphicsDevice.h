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
#include "WMRenderPipeline.h"

namespace WildMini::Graphics
{
    class WM_API WMGraphicsDevice : public WildMini::Object::WMRefCounter
    {
    public:
        static WMGraphicsDevice* CreateGraphicsDevice();

    public:
        virtual WildMini::Object::WMObject<WMCommandQueue> CreateCommandQueue() = 0;
        virtual WildMini::Object::WMObject<WMGPUBuffer> CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode) = 0;
        virtual WildMini::Object::WMObject<WMTexture> CreateTexture(const WMTexture::Desc& desc) = 0;
        virtual WildMini::Object::WMObject<WMRenderPipeline> CreateRenderPipeline(const WMRenderPipelineDescriptor& desc) = 0;

        virtual WildMini::Object::WMObject<WMShader> CreateShader(const std::wstring& path, const std::string& entry, WMShader::StageType stage);
        virtual WildMini::Object::WMObject<WMShader> CreateShader(const std::vector<uint8_t>& data, const std::string& entry, WMShader::StageType stage) = 0;
    };
}
