#pragma once
#ifdef _WIN32
#include <Windows.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include "IGraphicsDevice.h"
#include "Window/IWindow.h"

namespace Core
{
    class GraphicsDeviceContext : public Core::IGraphicsDevice
    {
    public:
        GraphicsDeviceContext();
        virtual ~GraphicsDeviceContext();

    private:
        ID3D12Device* device = nullptr;
        IDXGIFactory4* dxgiFactory = nullptr;
        ID3D12Fence* fence = nullptr;
        ID3D12CommandQueue* commandQueue = nullptr;
        ID3D12CommandAllocator* commandAllocator = nullptr;
        ID3D12GraphicsCommandList* commandList = nullptr;
        IDXGISwapChain* swapChain = nullptr;

        unsigned int rtvDescSize = 0;
        unsigned int dsvDescSize = 0;
        unsigned int cbvDescSize = 0;

        HWND hwnd;

    public:
        virtual void Create(IWindow* window) override;
    };
}
#endif  //  _WIN32
