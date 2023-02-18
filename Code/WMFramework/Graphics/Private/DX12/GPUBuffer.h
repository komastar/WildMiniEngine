//
//  File:   GPUBuffer.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "d3d12_include.h"
#include "Graphics/WMGPUBuffer.h"

namespace WildMini::Graphics::Private::DX12
{
    class GPUBuffer : public WildMini::Graphics::WMGPUBuffer
    {
    public:
        GPUBuffer(ComPtr<ID3D12Resource> buffer, WildMini::Graphics::WMGPUBuffer::CPUCacheMode mode, D3D12_RESOURCE_STATES state);
        virtual ~GPUBuffer();

    public:
        virtual size_t Size() const override;
        virtual bool IsWritable() const override;
        virtual bool IsReadable() const override;
        virtual bool WriteData(const void* data, size_t size) override;
        virtual bool WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize) override;
        virtual bool ReadData(void* data, size_t size) override;

        ID3D12Resource* Buffer() const { return buffer.Get(); }
        D3D12_RESOURCE_STATES InitialState() const { return state; }

    private:
        size_t size;
        bool writable;
        bool readable;
        ComPtr<ID3D12Resource> buffer;
        D3D12_RESOURCE_STATES state;
    };
}
