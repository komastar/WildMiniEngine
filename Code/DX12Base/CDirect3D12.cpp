#include "stdafx.h"
#include "CDirect3D12.h"


CDirect3D12::CDirect3D12() :
    m_isFullScreen(false),
    m_isVSyncEnable(false),
    m_ptScreenPos{ 0, 0 },
    m_ptScreenSize{ 0, 0 },
    m_fScreenDepth(0.0f),
    m_fScreenNear(0.0f),
    m_wsAppName("DX12App")
{
}


CDirect3D12::~CDirect3D12()
{
}

void CDirect3D12::InitWindow()
{
    DEVMODE dmScreenSettings;
    m_ptScreenSize.x = GetSystemMetrics(SM_CXSCREEN);
    m_ptScreenSize.y = GetSystemMetrics(SM_CYSCREEN);
    if (m_isFullScreen)
    {
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = (unsigned long)m_ptScreenSize.x;
        dmScreenSettings.dmPelsHeight = (unsigned long)m_ptScreenSize.y;
        dmScreenSettings.dmBitsPerPel = 32;
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

        m_ptScreenPos = { 0, 0 };
    }
    else
    {
        m_ptScreenSize = { 800, 600 };
        m_ptScreenPos.x = (GetSystemMetrics(SM_CXSCREEN) - m_ptScreenSize.x) / 2;
        m_ptScreenPos.y = (GetSystemMetrics(SM_CYSCREEN) - m_ptScreenSize.y) / 2;
    }
}

void CDirect3D12::InitInstance(WNDPROC proc)
{
    WNDCLASSEX wcex;

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = proc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = g_hInst;
    wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wcex.hIconSm = wcex.hIcon;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = m_wsAppName;
    wcex.cbSize = sizeof(WNDCLASSEX);

    RegisterClassEx(&wcex);

    HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_wsAppName, m_wsAppName,
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
        m_ptScreenPos.x, m_ptScreenPos.y,
        m_ptScreenSize.x, m_ptScreenSize.y,
        NULL, NULL, g_hInst, NULL);

    ShowWindow(hWnd, SW_SHOW);
    SetForegroundWindow(hWnd);
    SetFocus(hWnd);

    //   커서 숨기기
    ShowCursor(false);

    g_hWnd = hWnd;
}

BOOL CDirect3D12::InitDevice()
{
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_1;

    if (FAILED(D3D12CreateDevice(NULL, featureLevel, __uuidof(ID3D12Device), (void**)&m_pDevice)))
    {
        MessageBox(g_hWnd, "DirectX12.1 device create failed.", "DirectX Device Failure", MB_OK);
        return FALSE;
    }

    // Initialize the description of the command queue.
    D3D12_COMMAND_QUEUE_DESC commandQueueDesc;
    ZeroMemory(&commandQueueDesc, sizeof(commandQueueDesc));

    // Set up the description of the command queue.
    commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    commandQueueDesc.NodeMask = 0;

    // Create the command queue.
    m_pDevice->CreateCommandQueue(&commandQueueDesc, __uuidof(ID3D12CommandQueue), (void**)&m_commandQueue);
    

    // Create a DirectX graphics interface factory.
    IDXGIFactory4* factory;
    CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&factory);
    
    // Use the factory to create an adapter for the primary graphics interface (video card).
    IDXGIAdapter* adapter;
    factory->EnumAdapters(0, &adapter);
    
    // Enumerate the primary adapter output (monitor).
    IDXGIOutput* adapterOutput;
    adapter->EnumOutputs(0, &adapterOutput);
    
    // Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
    UINT numModes = 0;
    UINT numerator, denominator, renderTargetViewDescriptorSize;
    adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
    
    // Create a list to hold all the possible display modes for this monitor/video card combination.
    DXGI_MODE_DESC* displayModeList;
    displayModeList = new DXGI_MODE_DESC[numModes];
    if (!displayModeList)
    {
        return false;
    }

    // Now fill the display mode list structures.
    adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
    
    // Now go through all the display modes and find the one that matches the screen height and width.
    // When a match is found store the numerator and denominator of the refresh rate for that monitor.
    for (UINT i = 0; i < numModes; i++)
    {
        if (displayModeList[i].Height == (unsigned int)m_ptScreenSize.y
            && displayModeList[i].Width == (unsigned int)m_ptScreenSize.x)
        {
            numerator = displayModeList[i].RefreshRate.Numerator;
            denominator = displayModeList[i].RefreshRate.Denominator;
        }
    }

    // Release the display mode list.
    SAFE_DELETE_ARRAY(displayModeList);

    // Release the adapter output.
    SAFE_RELEASE(adapterOutput);

    // Release the adapter.
    SAFE_RELEASE(adapter);

    // Initialize the swap chain description.
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

    // Set the swap chain to use double buffering.
    swapChainDesc.BufferCount = 2;

    // Set the height and width of the back buffers in the swap chain.
    swapChainDesc.BufferDesc.Width = m_ptScreenSize.x;
    swapChainDesc.BufferDesc.Height = m_ptScreenSize.y;

    // Set a regular 32-bit surface for the back buffers.
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    // Set the usage of the back buffers to be render target outputs.
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    // Set the swap effect to discard the previous buffer contents after swapping.
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    // Set the handle for the window to render to.
    swapChainDesc.OutputWindow = g_hWnd;

    // Set to full screen or windowed mode.
    if (m_isFullScreen)
    {
        swapChainDesc.Windowed = false;
    }
    else
    {
        swapChainDesc.Windowed = true;
    }

    IDXGISwapChain* swapChain = nullptr;
    // Set the refresh rate of the back buffer.
    if (m_isVSyncEnable)
    {
        swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
    }
    else
    {
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    }

    // Turn multisampling off.
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    // Set the scan line ordering and scaling to unspecified.
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    // Don't set the advanced flags.
    swapChainDesc.Flags = 0;

    // Finally create the swap chain using the swap chain description.	
    D3D12_DESCRIPTOR_HEAP_DESC renderTargetViewHeapDesc;
    if (m_commandQueue)
    {
        factory->CreateSwapChain(m_commandQueue, &swapChainDesc, &swapChain);
    }
    
    // Next upgrade the IDXGISwapChain to a IDXGISwapChain3 interface and store it in a private member variable named m_swapChain.
    // This will allow us to use the newer functionality such as getting the current back buffer index.
    if (swapChain)
    {
        swapChain->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&m_swapChain);
    }
    
    // Clear pointer to original swap chain interface since we are using version 3 instead (m_swapChain).
    swapChain = 0;

    // Release the factory now that the swap chain has been created.
    SAFE_RELEASE(factory);

    // Initialize the render target view heap description for the two back buffers.
    D3D12_CPU_DESCRIPTOR_HANDLE renderTargetViewHandle;
    ZeroMemory(&renderTargetViewHeapDesc, sizeof(renderTargetViewHeapDesc));

    // Set the number of descriptors to two for our two back buffers.  Also set the heap tyupe to render target views.
    renderTargetViewHeapDesc.NumDescriptors = 2;
    renderTargetViewHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    renderTargetViewHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    // Create the render target view heap for the back buffers.
    m_pDevice->CreateDescriptorHeap(&renderTargetViewHeapDesc, __uuidof(ID3D12DescriptorHeap), (void**)&m_renderTargetViewHeap);
    
    // Get a handle to the starting memory location in the render target view heap to identify where the render target views will be located for the two back buffers.
    renderTargetViewHandle = m_renderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();

    // Get the size of the memory location for the render target view descriptors.
    renderTargetViewDescriptorSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    // Get a pointer to the first back buffer from the swap chain.
    m_swapChain->GetBuffer(0, __uuidof(ID3D12Resource), (void**)&m_backBufferRenderTarget[0]);
    
    // Create a render target view for the first back buffer.
    m_pDevice->CreateRenderTargetView(m_backBufferRenderTarget[0], NULL, renderTargetViewHandle);

    // Increment the view handle to the next descriptor location in the render target view heap.
    renderTargetViewHandle.ptr += renderTargetViewDescriptorSize;

    // Get a pointer to the second back buffer from the swap chain.
    m_swapChain->GetBuffer(1, __uuidof(ID3D12Resource), (void**)&m_backBufferRenderTarget[1]);
    
    // Create a render target view for the second back buffer.
    m_pDevice->CreateRenderTargetView(m_backBufferRenderTarget[1], NULL, renderTargetViewHandle);

    // Finally get the initial index to which buffer is the current back buffer.
    m_bufferIndex = m_swapChain->GetCurrentBackBufferIndex();

    // Create a command allocator.
    m_pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&m_commandAllocator);

    // Create a basic command list.
    m_pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator, NULL, __uuidof(ID3D12GraphicsCommandList), (void**)&m_commandList);
    
    // Initially we need to close the command list during initialization as it is created in a recording state.
    m_commandList->Close();
    
    // Create a fence for GPU synchronization.
    m_pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), (void**)&m_fence);
    
    // Create an event object for the fence.
    m_fenceEvent = CreateEventEx(NULL, FALSE, FALSE, EVENT_ALL_ACCESS);
    if (m_fenceEvent == NULL)
    {
        return FALSE;
    }

    // Initialize the starting fence value. 
    m_fenceValue = 1;

    return TRUE;
}

BOOL CDirect3D12::Render()
{
    HRESULT result;
    D3D12_RESOURCE_BARRIER barrier;
    D3D12_CPU_DESCRIPTOR_HANDLE renderTargetViewHandle;
    unsigned int renderTargetViewDescriptorSize;
    float color[4];
    ID3D12CommandList* ppCommandLists[1];
    unsigned long long fenceToWaitFor;


    // Reset (re-use) the memory associated command allocator.
    result = m_commandAllocator->Reset();
    if (FAILED(result))
    {
        return false;
    }

    // Reset the command list, use empty pipeline state for now since there are no shaders and we are just clearing the screen.
    result = m_commandList->Reset(m_commandAllocator, m_pipelineState);
    if (FAILED(result))
    {
        return false;
    }

    // Record commands in the command list now.
    // Start by setting the resource barrier.
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = m_backBufferRenderTarget[m_bufferIndex];
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    m_commandList->ResourceBarrier(1, &barrier);

    // Get the render target view handle for the current back buffer.
    renderTargetViewHandle = m_renderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();
    renderTargetViewDescriptorSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    if (m_bufferIndex == 1)
    {
        renderTargetViewHandle.ptr += renderTargetViewDescriptorSize;
    }

    // Set the back buffer as the render target.
    m_commandList->OMSetRenderTargets(1, &renderTargetViewHandle, FALSE, NULL);

    // Then set the color to clear the window to.
    color[0] = 0.5;
    color[1] = 0.5;
    color[2] = 0.5;
    color[3] = 1.0;
    m_commandList->ClearRenderTargetView(renderTargetViewHandle, color, 0, NULL);

    // Indicate that the back buffer will now be used to present.
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    m_commandList->ResourceBarrier(1, &barrier);

    // Close the list of commands.
    result = m_commandList->Close();
    if (FAILED(result))
    {
        return false;
    }

    // Load the command list array (only one command list for now).
    ppCommandLists[0] = m_commandList;

    // Execute the list of commands.
    m_commandQueue->ExecuteCommandLists(1, ppCommandLists);

    // Finally present the back buffer to the screen since rendering is complete.
    if (m_isVSyncEnable)
    {
        // Lock to screen refresh rate.
        result = m_swapChain->Present(1, 0);
        if (FAILED(result))
        {
            return false;
        }
    }
    else
    {
        // Present as fast as possible.
        result = m_swapChain->Present(0, 0);
        if (FAILED(result))
        {
            return false;
        }
    }

    // Signal and increment the fence value.
    fenceToWaitFor = m_fenceValue;
    result = m_commandQueue->Signal(m_fence, fenceToWaitFor);
    if (FAILED(result))
    {
        return false;
    }
    m_fenceValue++;

    // Wait until the GPU is done rendering.
    if (m_fence->GetCompletedValue() < fenceToWaitFor)
    {
        result = m_fence->SetEventOnCompletion(fenceToWaitFor, m_fenceEvent);
        if (FAILED(result))
        {
            return false;
        }
        WaitForSingleObject(m_fenceEvent, INFINITE);
    }

    // Alternate the back buffer index back and forth between 0 and 1 each frame.
    m_bufferIndex == 0 ? m_bufferIndex = 1 : m_bufferIndex = 0;

    return TRUE;
}

BOOL CDirect3D12::Release()
{
    CGameObject::Release();

    int error;


    // Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
    if (m_swapChain)
    {
        m_swapChain->SetFullscreenState(false, NULL);
    }

    // Close the object handle to the fence event.
    error = CloseHandle(m_fenceEvent);
    if (error == 0)
    {
    }

    // Release the fence.
    SAFE_RELEASE(m_fence);

    // Release the empty pipe line state.
    SAFE_RELEASE(m_pipelineState);

    // Release the command list.
    SAFE_RELEASE(m_commandList);

    // Release the command allocator.
    SAFE_RELEASE(m_commandAllocator);

    // Release the back buffer render target views.
    SAFE_RELEASE(m_backBufferRenderTarget[0]);
    SAFE_RELEASE(m_backBufferRenderTarget[1]);

    // Release the render target view heap.
    SAFE_RELEASE(m_renderTargetViewHeap);

    // Release the swap chain.
    SAFE_RELEASE(m_swapChain);

    // Release the command queue.
    SAFE_RELEASE(m_commandQueue);

    // Release the device.
    SAFE_RELEASE(m_pDevice);

    return 0;
}
