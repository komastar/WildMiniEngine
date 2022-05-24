#ifdef _WIN32
#include "Graphics/Platform/DX/GraphicsDeviceContext.h"
#include "Graphics/Platform/DX/CommandList.h"
#include "Window/IWindow.h"

Core::GraphicsDeviceContext::GraphicsDeviceContext(IWindow* window)
    : device(nullptr)
    , dxgiFactory(nullptr)
    , window(window)
    , commandList(nullptr)
    , commandAllocator(nullptr)
    , commandQueue(nullptr)
    , swapChain(nullptr)
{
    CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
    D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device));
}

Core::GraphicsDeviceContext::~GraphicsDeviceContext()
{
}

void Core::GraphicsDeviceContext::Create()
{
    CreateCommandQueue();
    CreateCommandAllocator();
    CreateCommandList();
    CreateSwapChain();
    commandList->Close();
}

void Core::GraphicsDeviceContext::CreateCommandQueue()
{
    commandQueue = new CommandQueue(device.Get());
}

void Core::GraphicsDeviceContext::CreateCommandAllocator()
{
    device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
}

void Core::GraphicsDeviceContext::CreateCommandList()
{
    commandList = new CommandList(device.Get(), commandAllocator.Get());
}

void Core::GraphicsDeviceContext::CreateSwapChain()
{
    swapChain = new SwapChain(device.Get(), dxgiFactory.Get(), window);
}
#endif // _WIN32
