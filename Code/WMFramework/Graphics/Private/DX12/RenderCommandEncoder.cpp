//
//  File:   RenderCommandEncoder.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "RenderCommandEncoder.h"
#include "Texture.h"

using namespace WildMini::Graphics::Private::DX12;
using namespace WildMini::Graphics::Primitive;

RenderCommandEncoder::RenderCommandEncoder(WMCommandBuffer* _commandBuffer, ID3D12GraphicsCommandList* _commandList)
    : commandList(_commandList)
    , commandBuffer(_commandBuffer)
{
}

void RenderCommandEncoder::SetViewport(const WMViewport& viewport)
{
    D3D12_VIEWPORT vp = {
        viewport.x, viewport.y,
        viewport.width, viewport.height,
        viewport.nearDepth, viewport.farDepth
    };
    commandList->RSSetViewports(1, &vp);
}

void RenderCommandEncoder::SetViewports(const Primitive::WMViewport* viewports, uint32_t count)
{
    std::vector<D3D12_VIEWPORT> viewportList(count);
    for (uint32_t i = 0; i < count; ++i)
    {
        viewportList[i].TopLeftX = viewports[i].x;
        viewportList[i].TopLeftY = viewports[i].y;
        viewportList[i].Width = viewports[i].width;
        viewportList[i].Height = viewports[i].height;
        viewportList[i].MinDepth = viewports[i].nearDepth;
        viewportList[i].MaxDepth = viewports[i].farDepth;
    }
    commandList->RSSetViewports(count, viewportList.data());
}

void RenderCommandEncoder::SetScissorRect(const WMRect& rect)
{
    D3D12_RECT scissorRect = {
        static_cast<LONG>(rect.x),
        static_cast<LONG>(rect.y),
        static_cast<LONG>(rect.x + rect.width),
        static_cast<LONG>(rect.y + rect.height)
    };
    commandList->RSSetScissorRects(1, &scissorRect);
}

void RenderCommandEncoder::SetScissorRects(const Primitive::WMRect* rects, uint32_t count)
{
    std::vector<D3D12_RECT> rectList(count);
    for (uint32_t i = 0; i < count; ++i)
    {
        rectList[i].left = static_cast<LONG>(rects[i].x);
        rectList[i].top = static_cast<LONG>(rects[i].y);
        rectList[i].right = static_cast<LONG>(rects[i].x + rects[i].width);
        rectList[i].bottom = static_cast<LONG>(rects[i].y + rects[i].height);
    }
    commandList->RSSetScissorRects(count, rectList.data());
}

void RenderCommandEncoder::SetRenderTargets(std::vector<const WMTexture*> renderTargets, const WMTexture* depthStencil)
{
    std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> renderTargetHandles;
    renderTargetHandles.reserve(renderTargets.size());
    for (const WMTexture* renderTarget : renderTargets)
    {
        const Texture* texture = dynamic_cast<const Texture*>(renderTarget);
        D3D12_CPU_DESCRIPTOR_HANDLE renderTargetHandle = texture->RenderTargetView();
        renderTargetHandles.push_back(renderTargetHandle);
        TransitionBufferState(texture->Resource(), texture->InitialState(), D3D12_RESOURCE_STATE_RENDER_TARGET);
    }

    if (const Texture* dsTexture = reinterpret_cast<const Texture*>(depthStencil))
    {
        D3D12_CPU_DESCRIPTOR_HANDLE dsView = dsTexture->DepthStencilView();
        commandList->OMSetRenderTargets(
            static_cast<UINT>(renderTargetHandles.size())
            , renderTargetHandles.data()
            , true
            , &dsView);
    }
    else
    {
        commandList->OMSetRenderTargets(
            static_cast<UINT>(renderTargetHandles.size())
            , renderTargetHandles.data()
            , false
            , nullptr);
    }

    for (const WMTexture* renderTarget : renderTargets)
    {
        const Texture* texture = reinterpret_cast<const Texture*>(renderTarget);
        TransitionBufferState(
            texture->Resource()
            , D3D12_RESOURCE_STATE_RENDER_TARGET
            , texture->InitialState());
    }
}

void RenderCommandEncoder::ClearRenderTarget(const WMTexture* renderTarget, const WMColor& color)
{
    const Texture* texture = reinterpret_cast<const Texture*>(renderTarget);
    TransitionBufferState(texture->Resource(), texture->InitialState(), D3D12_RESOURCE_STATE_RENDER_TARGET);
    commandList->ClearRenderTargetView(
        texture->RenderTargetView()
        , color.c
        , 0
        , nullptr);
    TransitionBufferState(texture->Resource(), D3D12_RESOURCE_STATE_RENDER_TARGET, texture->InitialState());
}

void RenderCommandEncoder::ClearDepthStencil(const WMTexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil)
{
    D3D12_CLEAR_FLAGS flag = D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL;
    switch (clearFlag)
    {
    case DepthStencilClearFlag::Depth:
        flag = D3D12_CLEAR_FLAG_DEPTH;
        break;
    case DepthStencilClearFlag::Stencil:
        flag = D3D12_CLEAR_FLAG_STENCIL;
        break;
    }

    const Texture* ds = reinterpret_cast<const Texture*>(depthStencil);
    commandList->ClearDepthStencilView(ds->DepthStencilView(), flag, clearDepth, clearStencil, 0, nullptr);
}

void RenderCommandEncoder::TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before)
{
    if (before != after)
    {
        CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(buffer, before, after);
        commandList->ResourceBarrier(1, &barrier);
    }
}

void RenderCommandEncoder::EndEncoding()
{
    commandList->Close();
    commandList = nullptr;
}
