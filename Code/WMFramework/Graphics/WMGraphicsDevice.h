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

namespace WildMini
{
    class WM_API WMGraphicsDevice : public WMRefCounter
    {
    public:
        static WMGraphicsDevice* CreateGraphicsDevice();

    public:
        virtual WMSharedPtr<WMCommandQueue> CreateCommandQueue() = 0;
        virtual WMSharedPtr<WMGPUBuffer> CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode) = 0;
        virtual WMSharedPtr<WMTexture> CreateTexture(const WMTexture::Desc& desc) = 0;
        virtual WMSharedPtr<WMRenderPipeline> CreateRenderPipeline(const WMRenderPipelineDescriptor& desc) = 0;

        virtual WMSharedPtr<WMShader> CreateShader(const std::wstring& path, const std::string& entry, WMShader::StageType stage);
        virtual WMSharedPtr<WMShader> CreateShader(const Vector<uint8_t>& data, const std::string& entry, WMShader::StageType stage) = 0;
    };
}
