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

namespace WildMini
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
        virtual WMSharedPtr<WMCommandQueue> CreateCommandQueue() override;
        virtual WMSharedPtr<WMGPUBuffer> CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode) override;
        virtual WMSharedPtr<WMTexture> CreateTexture(const WMTexture::Desc& desc) override;
        virtual WMSharedPtr<WMRenderPipeline> CreateRenderPipeline(const WMRenderPipelineDescriptor& desc) override;

        virtual WMSharedPtr<WMShader> CreateShader(const Vector<uint8_t>& data, const std::string& entry, WMShader::StageType stage) override;

    public:
        void CreateImguiDescriptorHeap(uint32_t frameCount);

    public:
        ID3D12Device* Device() const { return device.Get(); }
        ComPtr<IDXGIFactory4> Factory() const { return dxgiFactory; }
    };
}
#endif  //  _WIN32
