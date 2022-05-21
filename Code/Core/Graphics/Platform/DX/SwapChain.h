#pragma once
#include "d3d12_include.h"
#include "Graphics/ISwapChain.h"
#include "Window/IWindow.h"

namespace Core
{
    class SwapChain : public ISwapChain
    {
    public:
        SwapChain(IDXGISwapChain* swapChain, uint32_t width, uint32_t height);

    public:
        void Resize(uint32_t width, uint32_t height);

    public:
        uint32_t Width();
        uint32_t Height();

    private:
        ComPtr<IDXGISwapChain> swapChain;

        uint32_t width;
        uint32_t height;
    };
}
