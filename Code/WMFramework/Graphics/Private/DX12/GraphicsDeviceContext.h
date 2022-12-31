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

    public:
        ComPtr<ID3D12DescriptorHeap> imguiDescHeap;

    private:
        ComPtr<IDXGIFactory4> dxgiFactory;
        ComPtr<ID3D12Device> device;

    public:
        virtual WildMini::WMSharedPtr<WildMini::Graphics::WMCommandQueue> CreateCommandQueue() override;
        virtual WildMini::WMSharedPtr<WildMini::Graphics::WMGPUBuffer> CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode) override;
        virtual WildMini::WMSharedPtr<WildMini::Graphics::WMTexture> CreateTexture(const WMTexture::Desc& desc) override;
        virtual WildMini::WMSharedPtr<WildMini::Graphics::WMRenderPipeline> CreateRenderPipeline(const WMRenderPipelineDescriptor& desc) override;

        virtual WildMini::WMSharedPtr<WMShader> CreateShader(const std::vector<uint8_t>& data, const std::string& entry, WMShader::StageType stage) override;

    public:
        void CreateImguiDescriptorHeap(uint32_t frameCount);

    public:
        ID3D12Device* Device() const { return device.Get(); }
        ComPtr<IDXGIFactory4> Factory() const { return dxgiFactory; }
    };
}
#endif  //  _WIN32
