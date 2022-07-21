//
//  File:   RenderCommandEncoder.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "RenderCommandEncoder.h"
#include "Texture.h"
#include "GPUBuffer.h"
#include "imgui.h"
#include "backends/imgui_impl_dx12.h"
#include "backends/imgui_impl_win32.h"

using namespace WildMini::Graphics::Private::DX12;
using namespace WildMini::Graphics::Primitive;

RenderCommandEncoder::RenderCommandEncoder(ID3D12DescriptorHeap* _imguiDescHeap, RenderPipeline* _renderPipeline, WMCommandBuffer* _commandBuffer, ID3D12GraphicsCommandList* _commandList)
    : commandList(_commandList)
    , commandBuffer(_commandBuffer)
    , imguiDescHeap(_imguiDescHeap)
{
    commandList->SetGraphicsRootSignature(_renderPipeline->RootSignature());

    ImGui_ImplDX12_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}


RenderCommandEncoder::~RenderCommandEncoder()
{
    commandList = nullptr;
    commandBuffer = nullptr;
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
    renderTargetsTemp = renderTargets;
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
    const Texture* texture = dynamic_cast<const Texture*>(renderTarget);
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

void RenderCommandEncoder::TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after)
{
    if (before != after)
    {
        CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(buffer, before, after);
        commandList->ResourceBarrier(1, &barrier);
    }
}

void RenderCommandEncoder::SetPrimitiveType(PrimitiveType primitiveType)
{
    switch (primitiveType)
    {
    case WildMini::Graphics::WMRenderCommandEncoder::PrimitiveType::Line:
        commandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
        break;
    case WildMini::Graphics::WMRenderCommandEncoder::PrimitiveType::LineStrip:
        commandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
        break;
    case WildMini::Graphics::WMRenderCommandEncoder::PrimitiveType::Triangle:
        commandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        break;
    case WildMini::Graphics::WMRenderCommandEncoder::PrimitiveType::TriangleStrip:
        commandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
        break;
    case WildMini::Graphics::WMRenderCommandEncoder::PrimitiveType::Point:
        commandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
    default:
        break;
    }
}

void RenderCommandEncoder::SetConstantBuffer(uint32_t index, const WMGPUBuffer* constantBuffer)
{
    const GPUBuffer* buffer = dynamic_cast<const GPUBuffer*>(constantBuffer);
    commandList->SetGraphicsRootConstantBufferView(index, buffer->Buffer()->GetGPUVirtualAddress());
}

void RenderCommandEncoder::SetVertexBuffer(const WMGPUBuffer* vertexBuffer, uint32_t vertexSize)
{
    const GPUBuffer* buffer = dynamic_cast<const GPUBuffer*>(vertexBuffer);
    D3D12_VERTEX_BUFFER_VIEW view;
    view.BufferLocation = buffer->Buffer()->GetGPUVirtualAddress();
    view.StrideInBytes = vertexSize;
    view.SizeInBytes = static_cast<UINT>(buffer->Size());
    commandList->IASetVertexBuffers(0, 1, &view);
}

void RenderCommandEncoder::DrawPrimitives(PrimitiveType primitiveType, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t instanceStart)
{
    SetPrimitiveType(primitiveType);
    for (const WMTexture* renderTarget : renderTargetsTemp)
    {
        const Texture* texture = reinterpret_cast<const Texture*>(renderTarget);
        TransitionBufferState(
            texture->Resource()
            , texture->InitialState()
            , D3D12_RESOURCE_STATE_RENDER_TARGET);
    }
    commandList->DrawInstanced(vertexCount, instanceCount, vertexStart, instanceStart);
    for (const WMTexture* renderTarget : renderTargetsTemp)
    {
        const Texture* texture = reinterpret_cast<const Texture*>(renderTarget);
        TransitionBufferState(
            texture->Resource()
            , D3D12_RESOURCE_STATE_RENDER_TARGET
            , texture->InitialState());
    }
}

void RenderCommandEncoder::ImguiShowDemoWindow()
{
    static bool isShowDemo = true;
    if (isShowDemo)
    {
        ImGui::ShowDemoWindow(&isShowDemo);
    }
    ImGui::Render();
}

void RenderCommandEncoder::EndEncoding()
{
    commandList->SetDescriptorHeaps(1, imguiDescHeap.GetAddressOf());
    ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList.Get());
    commandList->Close();
    commandList = nullptr;
}
