#ifdef _WIN32
#include "Graphics/Platform/DX/GraphicsDeviceContext.h"
#include "Math/Math.h"
#include "Graphics/Platform/DX/CommandList.h"

Core::GraphicsDeviceContext::GraphicsDeviceContext()
    : device(nullptr)
    , dxgiFactory(nullptr)
    , window(nullptr)
    , commandList(nullptr)
    , commandAllocator(nullptr)
    , commandQueue(nullptr)
    , swapChain(nullptr)
{
}

Core::GraphicsDeviceContext::~GraphicsDeviceContext()
{
}

void Core::GraphicsDeviceContext::Create(IWindow* window)
{
    this->window = window;
    CreateDevice();
    CreateCommandQueue();
    CreateCommandAllocator();
    CreateCommandList();
    CreateSwapChain();
    commandList->Close();
}

void Core::GraphicsDeviceContext::Update()
{
}

void Core::GraphicsDeviceContext::Render()
{
}

void Core::GraphicsDeviceContext::CreateDevice()
{
    CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
    D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device));
}

void Core::GraphicsDeviceContext::CreateCommandQueue()
{
    commandQueue = new CommandQueue(device.Get());
}

void Core::GraphicsDeviceContext::CreateCommandAllocator()
{
    commandAllocator = new CommandAllocator(device.Get());
}

void Core::GraphicsDeviceContext::CreateCommandList()
{
    commandList = new CommandList(device.Get(), commandAllocator);
}

void Core::GraphicsDeviceContext::CreateSwapChain()
{
    swapChain = new SwapChain(device.Get(), dxgiFactory.Get(), window);
}
#endif // _WIN32
