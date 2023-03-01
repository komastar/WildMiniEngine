//
//  File:   GPUBuffer.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "GPUBuffer.h"

using namespace WildMini;

GPUBuffer::GPUBuffer(ComPtr<ID3D12Resource> buffer, WMGPUBuffer::CPUCacheMode mode, D3D12_RESOURCE_STATES state)
    : buffer(buffer)
    , state(state)
    , writable(WMGPUBuffer::CPUCacheMode::WRITABLE == mode)
    , readable(WMGPUBuffer::CPUCacheMode::READABLE == mode)
{
    WMASSERT(buffer);
    size = buffer->GetDesc().Width;
}

GPUBuffer::~GPUBuffer()
{
}

size_t GPUBuffer::Size() const
{
    return size;
}

bool GPUBuffer::IsWritable() const
{
    return writable;
}

bool GPUBuffer::IsReadable() const
{
    return readable;
}

bool GPUBuffer::WriteData(const void* data, size_t size)
{
    BYTE* mappedGPUdata = nullptr;
    D3D12_RANGE readRange(0, 0);
    if SUCCEEDED(buffer->Map(0, &readRange, reinterpret_cast<void**>(&mappedGPUdata)))
    {
        memcpy(mappedGPUdata, data, size);

        D3D12_RANGE writeRange(0, size);
        buffer->Unmap(0, &writeRange);

        return true;
    }

    return false;
}

bool GPUBuffer::WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize)
{
    BYTE* mappedGPUdata = nullptr;
    D3D12_RANGE readRange(0, 0);
    if (SUCCEEDED(buffer->Map(0, &readRange, reinterpret_cast<void**>(&mappedGPUdata))))
    {
        size_t rowPitch = width * formatSize;
        size_t alignedRowPitch = AlignTextureRowPitch(rowPitch);

        const BYTE* cpuData = reinterpret_cast<const BYTE*>(const_cast<void*>(data));
        for (size_t i = 0; i < height; ++i)
        {
            memcpy(mappedGPUdata + alignedRowPitch * i, reinterpret_cast<const void*>(cpuData + rowPitch * i), rowPitch);
        }

        D3D12_RANGE writeRange(0, rowPitch * height);
        buffer->Unmap(0, &writeRange);
        return true;
    }

    return false;
}

bool GPUBuffer::ReadData(void* data, size_t size)
{
    BYTE* mappedGPUdata = nullptr;
    D3D12_RANGE readRange(0, size);
    if (SUCCEEDED(buffer->Map(0, &readRange, reinterpret_cast<void**>(&mappedGPUdata))))
    {
        memcpy(data, mappedGPUdata, size);

        D3D12_RANGE writeRange(0, 0);
        buffer->Unmap(0, &writeRange);
        return true;
    }
    return false;
}
