#include "D3D12Device.h"

void D3D12Device::Create(int width, int height)
{
    CreateDXGIFactory1(__uuidof(IDXGIFactory4), reinterpret_cast<void**>(&dxgiFactory));
    HRESULT result = D3D12CreateDevice(nullptr
        , D3D_FEATURE_LEVEL_12_0
        , __uuidof(ID3D12Device)
        , reinterpret_cast<void**>(&device));

    if (FAILED(result))
    {
        IDXGIAdapter* warpAdapter;
        dxgiFactory->EnumWarpAdapter(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&warpAdapter));
        D3D12CreateDevice(warpAdapter
            , D3D_FEATURE_LEVEL_12_0
            , __uuidof(IDXGIAdapter)
            , reinterpret_cast<void**>(&warpAdapter));
    }

    device->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), reinterpret_cast<void**>(&fence));

    rtvDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    dsvDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
    cbvDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT
        , __uuidof(ID3D12CommandAllocator)
        , reinterpret_cast<void**>(&commandAllocator));

    if (nullptr == commandAllocator)
    {
        return;
    }

    device->CreateCommandList(0
        , D3D12_COMMAND_LIST_TYPE_DIRECT
        , commandAllocator
        , nullptr
        , __uuidof(ID3D12GraphicsCommandList)
        , reinterpret_cast<void**>(&commandList));
    commandList->Close();

    D3D12_COMMAND_QUEUE_DESC commandQueueDesc = {};
    commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    device->CreateCommandQueue(&commandQueueDesc
        , __uuidof(ID3D12CommandQueue)
        , reinterpret_cast<void**>(&commandQueue));

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.OutputWindow = hwnd;
    swapChainDesc.Windowed = true;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    if (nullptr == commandQueue)
    {
        return;
    }
    dxgiFactory->CreateSwapChain(commandQueue, &swapChainDesc, &swapChain);
}

void D3D12Device::SetWindow(HWND hwnd)
{
    this->hwnd = hwnd;
}