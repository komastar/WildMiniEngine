//
//  File:   Texture.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "d3d12_include.h"
#include "Graphics/WMTexture.h"

namespace WildMini
{
    class GPUBuffer;
    class Texture : public WMTexture
    {
    public:
        Texture(WMSharedPtr<GPUBuffer> buffer, D3D12_RESOURCE_DESC desc);
        virtual ~Texture();

    public:
        virtual size_t Size() const override;
        virtual uint32_t Width() const override;
        virtual uint32_t Height() const override;
        virtual WMPixelFormat Format() const override;
        virtual void Write(const void* data) override;
        virtual const WMGPUBuffer* Buffer() const override;

        ID3D12Resource* Resource() const;
        D3D12_RESOURCE_STATES InitialState() const { return state; }

        void SetRenderTargetViewHeap(ID3D12DescriptorHeap* heap);
        void SetDepthStencilViewHeap(ID3D12DescriptorHeap* heap);
        void SetShaderResourceViewHeap(ID3D12DescriptorHeap* heap);

        D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView() const;
        D3D12_CPU_DESCRIPTOR_HANDLE ShaderResourceView() const;
        D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;

    private:
        size_t size;
        uint32_t width;
        uint32_t height;
        WMPixelFormat format;
        WMSharedPtr<WMGPUBuffer> buffer;
        D3D12_RESOURCE_STATES state;
        ID3D12Resource* resource;

        ComPtr<ID3D12DescriptorHeap> renderTargetViewHeap;
        ComPtr<ID3D12DescriptorHeap> depthStencilViewHeap;
        ComPtr<ID3D12DescriptorHeap> shaderResourceViewHeap;
    };
}
