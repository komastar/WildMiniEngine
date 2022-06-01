#pragma once
#include "d3d12_include.h"
#include "Graphics/WMSwapChain.h"
#include "Window/WMWindow.h"

namespace WildMini::Graphics::Private::DX12
{
    class SwapChain : public WMSwapChain
    {
    public:
        SwapChain(ID3D12Device* device, IDXGIFactory4* dxgiFactory, WildMini::Window::WMWindow* window);
        enum { BUFFER_COUNT = 2 };

    public:
        void Resize(uint32_t width, uint32_t height);

    public:
        uint32_t Width();
        uint32_t Height();

    private:
        ComPtr<IDXGISwapChain> swapChain;

        uint32_t width;
        uint32_t height;
        uint32_t swapChainIndex = 0;
    };
}
