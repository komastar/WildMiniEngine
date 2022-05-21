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

void Core::GraphicsDeviceContext::Update()
{
}

void Core::GraphicsDeviceContext::Render()
{
}

void Core::GraphicsDeviceContext::CreateCommandQueue()
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    ID3D12CommandQueue* pCommandQueue;
    device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&pCommandQueue));
    commandQueue = new CommandQueue(pCommandQueue);
}

void Core::GraphicsDeviceContext::CreateCommandAllocator()
{
    device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
}

void Core::GraphicsDeviceContext::CreateCommandList()
{
    ID3D12GraphicsCommandList* pCommandList;
    device->CreateCommandList(0
        , D3D12_COMMAND_LIST_TYPE_DIRECT
        , this->commandAllocator.Get()
        , nullptr
        , IID_PPV_ARGS(&pCommandList));
    commandList = new CommandList(pCommandList, commandAllocator.Get());
}

void Core::GraphicsDeviceContext::CreateSwapChain()
{
    uint32_t width = window->Width();
    uint32_t height = window->Height();

    DXGI_SWAP_CHAIN_DESC sd;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 2;
    sd.OutputWindow = reinterpret_cast<HWND>(window->PlatformHandle());
    sd.Windowed = true;
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    IDXGISwapChain* pSwapChain;
    dxgiFactory->CreateSwapChain(device.Get(), &sd, &pSwapChain);

    swapChain = new SwapChain(pSwapChain, width, height);
}
#endif // _WIN32
