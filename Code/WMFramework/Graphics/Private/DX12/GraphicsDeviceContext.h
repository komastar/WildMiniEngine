//
//  File:   GraphicsDeviceContext.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#ifdef _WIN32
#include "d3d12_include.h"
#include "Graphics/WMGraphicsDevice.h"

namespace WildMini::Graphics::Private
{
    class GraphicsDeviceContext : public WMGraphicsDevice
    {
    public:
        GraphicsDeviceContext();
        virtual ~GraphicsDeviceContext();

    private:
        ComPtr<IDXGIFactory4> dxgiFactory;
        ComPtr<ID3D12Device> device;

    public:
        virtual WildMini::Object::WMObject<WildMini::Graphics::WMCommandQueue> CreateCommandQueue() override;
        virtual WildMini::Object::WMObject<WildMini::Graphics::WMGPUBuffer> CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode) override;
        virtual WildMini::Object::WMObject<WildMini::Graphics::WMTexture> CreateTexture(const WMTexture::Desc& desc) override;
        virtual WildMini::Object::WMObject<WildMini::Graphics::WMRenderPipeline> CreateRenderPipeline(const WMRenderPipelineDescriptor& desc) override;

    public:
        ID3D12Device* Device() const { return device.Get(); }
        ComPtr<IDXGIFactory4> Factory() const { return dxgiFactory; }
    };
}
#endif  //  _WIN32
