#pragma once
#include "GraphicsDevice.h"
#include <Windows.h>
#include <dxgi1_4.h>
#include <d3d12.h>

class D3D12Device : public GraphicsDevice
{
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
    virtual void Create(int width, int height) override;

    void SetWindow(HWND hwnd);
};

