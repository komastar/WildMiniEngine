#include "Graphics/Platform/DX/SwapChain.h"
#include <Windows.h>

Core::SwapChain::SwapChain(ID3D12Device* device, IDXGIFactory4* dxgiFactory, IWindow* window)
    : swapChain(nullptr)
    , width(window->Width())
    , height(window->Height())
{
    DXGI_SWAP_CHAIN_DESC sd;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 2;
    sd.OutputWindow = reinterpret_cast<HWND>(window->PlatformHandle());
    sd.Windowed = true;
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    dxgiFactory->CreateSwapChain(device, &sd, &swapChain);
}

void Core::SwapChain::Resize(uint32_t width, uint32_t height)
{
    this->width = width;
    this->height = height;
}

uint32_t Core::SwapChain::Width()
{
    return width;
}

uint32_t Core::SwapChain::Height()
{
    return height;
}