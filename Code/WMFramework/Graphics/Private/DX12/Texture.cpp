//
//  File:   Texture.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "Texture.h"
#include "Type.h"

using namespace WildMini::Graphics;
using namespace WildMini::Graphics::Private::DX12;

Texture::Texture(ComPtr<ID3D12Resource> buffer, D3D12_RESOURCE_STATES state)
    : buffer(buffer)
    , state(state)
{
    D3D12_RESOURCE_DESC desc = buffer->GetDesc();
    width = static_cast<uint32_t>(desc.Width);
    height = static_cast<uint32_t>(desc.Height);
    format = ToPixelFormat(desc.Format);
    size = AlignTextureRowPitch(width * PixelFormatSize(format)) * height;
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
