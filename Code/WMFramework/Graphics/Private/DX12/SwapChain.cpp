//
//  File:   SwapChain.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "SwapChain.h"
#include <Windows.h>
#include "UI/imgui/imgui.h"
#include "UI/imgui/backends/imgui_impl_dx12.h"
#include "UI/imgui/backends/imgui_impl_win32.h"

using namespace WildMini::Graphics;
using namespace WildMini::Graphics::Private::DX12;
using namespace WildMini::Window;

SwapChain::SwapChain(GraphicsDeviceContext* _device, CommandQueue* _commandQueue, WindowContext* _window)
    : device(_device)
    , swapChain(nullptr)
    , width(_window->width)
    , height(_window->height)
    , imguiDescHeap(nullptr)
{
    DXGI_SWAP_CHAIN_DESC1 sd{};
    sd.Width = width;
    sd.Height = height;
    sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferCount = BUFFER_COUNT;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Scaling = DXGI_SCALING_NONE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    sd.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    ComPtr<IDXGISwapChain1> pSwapChain;
    HWND hwnd = reinterpret_cast<HWND>(_window->PlatformHandle());
    device->Factory()->CreateSwapChainForHwnd(_commandQueue->Queue()
        , hwnd
        , &sd
        , nullptr
        , nullptr
        , pSwapChain.GetAddressOf());

    pSwapChain.As(&swapChain);

    swapChainIndex = swapChain->GetCurrentBackBufferIndex();
    SetupRenderTargets();
    SetupDepthStencil();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hwnd);
    device->CreateImguiDescriptorHeap(BUFFER_COUNT);
}

void SwapChain::Resize(uint32_t width, uint32_t height)
{
    this->width = width;
    this->height = height;

    DXGI_SWAP_CHAIN_DESC desc;
    swapChain->GetDesc(&desc);
    for (int i = 0; i < BUFFER_COUNT; ++i)
    {
        renderTargets[i] = nullptr;
    }
    swapChain->ResizeBuffers(BUFFER_COUNT, this->width, this->height, desc.BufferDesc.Format, desc.Flags);
    swapChainIndex = swapChain->GetCurrentBackBufferIndex();
    SetupRenderTargets();
    SetupDepthStencil();
}

uint32_t SwapChain::Width()
{
    return width;
}

uint32_t SwapChain::Height()
{
    return height;
}

void SwapChain::SetupRenderTargets()
{
    for (UINT i = 0; i < BUFFER_COUNT; ++i)
    {
        ComPtr<ID3D12Resource> buffer;
        swapChain->GetBuffer(i, IID_PPV_ARGS(&buffer));
        D3D12_RESOURCE_DESC desc = buffer->GetDesc();
        renderTargets[i] = new Texture(buffer.Get(), D3D12_RESOURCE_STATE_PRESENT);

        D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        heapDesc.NodeMask = 0;
        heapDesc.NumDescriptors = 1;

        ComPtr<ID3D12DescriptorHeap> descHeap;
        device->Device()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(descHeap.GetAddressOf()));

        D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
        rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

        device->Device()->CreateRenderTargetView(buffer.Get()
            , &rtvDesc
            , descHeap->GetCPUDescriptorHandleForHeapStart());

        renderTargets[i]->SetRenderTargetViewHeap(descHeap.Get());
    }
}

void SwapChain::SetupDepthStencil()
{
    ComPtr<ID3D12Resource> buffer;
    CD3DX12_HEAP_PROPERTIES heapProp(D3D12_HEAP_TYPE_DEFAULT);
    D3D12_RESOURCE_DESC bufferDesc = {};
    bufferDesc.Width = width;
    bufferDesc.Height = height;
    bufferDesc.DepthOrArraySize = 1;
    bufferDesc.MipLevels = 1;
    bufferDesc.SampleDesc.Count = 1;
    bufferDesc.SampleDesc.Quality = 0;
    bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    bufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE | D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
    bufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    D3D12_CLEAR_VALUE clearValue;
    clearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    clearValue.DepthStencil.Depth = 0.0f;
    clearValue.DepthStencil.Stencil = 0;
    device->Device()->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &clearValue, IID_PPV_ARGS(buffer.GetAddressOf()));

    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
    dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    ComPtr<ID3D12DescriptorHeap> descHeap;
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    heapDesc.NumDescriptors = 1;
    device->Device()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(descHeap.GetAddressOf()));

    device->Device()->CreateDepthStencilView(buffer.Get()
        , &dsvDesc
        , descHeap->GetCPUDescriptorHandleForHeapStart());
    depthStencilTexture = new Texture(buffer.Get(), D3D12_RESOURCE_STATE_DEPTH_WRITE);
    depthStencilTexture->SetDepthStencilViewHeap(descHeap.Get());
}

const WMTexture* SwapChain::RenderTargetTexture() const
{
    return renderTargets[swapChainIndex];
}

const WMTexture* SwapChain::DepthStencilTexture() const
{
    return depthStencilTexture;
}

void SwapChain::Present()
{
    swapChain->Present(0, 0);
    swapChainIndex = ++swapChainIndex % BUFFER_COUNT;
}
