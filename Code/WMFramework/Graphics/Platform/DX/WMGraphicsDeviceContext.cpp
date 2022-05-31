#ifdef _WIN32
#include "Graphics/Platform/DX/WMGraphicsDeviceContext.h"
#include "Window/WMWindow.h"

using namespace WildMini::Graphics;
using namespace WildMini::Window;

WMGraphicsDeviceContext::WMGraphicsDeviceContext(WMWindow* window)
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

WMGraphicsDeviceContext::~WMGraphicsDeviceContext()
{
}

void WMGraphicsDeviceContext::Create()
{
    CreateCommandQueue();
    CreateCommandAllocator();
    CreateCommandList();
    CreateSwapChain();
    commandList->Close();
}

void WMGraphicsDeviceContext::CreateCommandQueue()
{
    commandQueue = new WMCommandQueueImpl(device.Get());
}

void WMGraphicsDeviceContext::CreateCommandAllocator()
{
    device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
}

void WMGraphicsDeviceContext::CreateCommandList()
{
    commandList = new WMCommandListImpl(device.Get(), commandAllocator.Get());
}

void WMGraphicsDeviceContext::CreateSwapChain()
{
    swapChain = new WMSwapChainImpl(device.Get(), dxgiFactory.Get(), window);
}
#endif // _WIN32
