#include "Graphics/Platform/DX/SwapChain.h"
#include <Windows.h>

Core::SwapChain::SwapChain(IDXGISwapChain* swapChain, uint32_t width, uint32_t height)
    : swapChain(nullptr)
    , width(width)
    , height(height)
{
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
