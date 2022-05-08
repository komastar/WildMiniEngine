#pragma once
#include "Application/Application.h"
#include <Windows.h>
#include <dxgi1_4.h>
#include <d3d12.h>

class WindowsApplication : public Application
{
private:
    HINSTANCE instance;
    HWND hwnd;

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

    const int width = 1024;
    const int height = 768;

public:
    WindowsApplication(HINSTANCE hinst);

public:
    virtual void OnInitialize() override;
    virtual void OnTerminate() override;
    virtual void Run() override;

private:
    void InitAppWindow();
    void InitD3D();
};

