//
//  File:   Texture.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "Texture.h"
#include "Type.h"
#include "Graphics/Private/DX12/GPUBuffer.h"

using namespace WildMini;

Texture::Texture(WMSharedPtr<GPUBuffer> InBuffer, D3D12_RESOURCE_DESC desc)
    : buffer(InBuffer)
    , state(InBuffer->InitialState())
    , resource(InBuffer->Buffer())
{
    width = static_cast<uint32_t>(desc.Width);
    height = static_cast<uint32_t>(desc.Height);
    format = ToPixelFormat(desc.Format);
    ID3D12Device* device = nullptr;
    resource->GetDevice(IID_PPV_ARGS(&device));
    device->GetCopyableFootprints(&desc, 0, 1, 0, nullptr, 0, 0, &size);
}

Texture::~Texture()
{
}

size_t Texture::Size() const
{
    return size;
}

uint32_t Texture::Width() const
{
    return width;
}

uint32_t Texture::Height() const
{
    return height;
}

WMPixelFormat Texture::Format() const
{
    return format;
}

void Texture::Write(const void* data)
{
    buffer->WriteDataForTexture(data, width, height, PixelFormatSize(format));
}

const WMGPUBuffer* Texture::Buffer() const
{
    return buffer;
}

ID3D12Resource* Texture::Resource() const
{
    return resource;
}

void Texture::SetRenderTargetViewHeap(ID3D12DescriptorHeap* heap)
{
    renderTargetViewHeap = heap;
}

void Texture::SetDepthStencilViewHeap(ID3D12DescriptorHeap* heap)
{
    depthStencilViewHeap = heap;
}

void Texture::SetShaderResourceViewHeap(ID3D12DescriptorHeap* heap)
{
    shaderResourceViewHeap = heap;
}

D3D12_CPU_DESCRIPTOR_HANDLE Texture::RenderTargetView() const
{
    return renderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();
}

D3D12_CPU_DESCRIPTOR_HANDLE Texture::DepthStencilView() const
{
    return depthStencilViewHeap->GetCPUDescriptorHandleForHeapStart();
}

D3D12_CPU_DESCRIPTOR_HANDLE Texture::ShaderResourceView() const
{
    return shaderResourceViewHeap->GetCPUDescriptorHandleForHeapStart();
}
