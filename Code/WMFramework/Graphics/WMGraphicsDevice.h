//
//  File:   WMGraphicsDevice.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMSharedPtr.h"
#include "WMCommandQueue.h"
#include "WMGPUBuffer.h"
#include "WMTexture.h"
#include "WMRenderPipeline.h"

namespace WildMini::Graphics
{
    class WM_API WMGraphicsDevice : public WildMini::WMRefCounter
    {
    public:
        static WMGraphicsDevice* CreateGraphicsDevice();

    public:
        virtual WildMini::WMSharedPtr<WMCommandQueue> CreateCommandQueue() = 0;
        virtual WildMini::WMSharedPtr<WMGPUBuffer> CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode) = 0;
        virtual WildMini::WMSharedPtr<WMTexture> CreateTexture(const WMTexture::Desc& desc) = 0;
        virtual WildMini::WMSharedPtr<WMRenderPipeline> CreateRenderPipeline(const WMRenderPipelineDescriptor& desc) = 0;

        virtual WildMini::WMSharedPtr<WMShader> CreateShader(const std::wstring& path, const std::string& entry, WMShader::StageType stage);
        virtual WildMini::WMSharedPtr<WMShader> CreateShader(const std::vector<uint8_t>& data, const std::string& entry, WMShader::StageType stage) = 0;
    };
}
