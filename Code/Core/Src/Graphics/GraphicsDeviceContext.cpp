#ifdef _WIN32
#include "Graphics/GraphicsDeviceContext.h"
#include "Math/Math.h"
#include <DirectXColors.h>>

using namespace DirectX;

Core::GraphicsDeviceContext::GraphicsDeviceContext()
    : device(nullptr)
    , dxgiFactory(nullptr)
    , fence(nullptr)
    , commandQueue(nullptr)
    , commandAllocator(nullptr)
    , commandList(nullptr)
    , swapChain(nullptr)
    , vsShaderByteCode(nullptr)
    , psShaderByteCode(nullptr)
{
}

Core::GraphicsDeviceContext::~GraphicsDeviceContext()
{
    uploadBuffer->Unmap(0, nullptr);
    uploadBuffer = nullptr;

    delete vsShaderByteCode;
    vsShaderByteCode = nullptr;

    delete psShaderByteCode;
    psShaderByteCode = nullptr;

    delete commandList;
    commandList = nullptr;

    delete commandAllocator;
    commandAllocator = nullptr;

    delete commandQueue;
    commandQueue = nullptr;

    delete fence;
    fence = nullptr;

    delete dxgiFactory;
    dxgiFactory = nullptr;

    delete device;
    device = nullptr;
}

void Core::GraphicsDeviceContext::Create(IWindow* window)
{
    this->window = window;

    HRESULT hr = S_OK;

    //  NOTE : create device
    hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
    hr = D3D12CreateDevice(nullptr
        , D3D_FEATURE_LEVEL_12_0
        , IID_PPV_ARGS(&device));

    if (FAILED(hr))
    {
        IDXGIAdapter* warpAdapter;
        dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter));
        hr = D3D12CreateDevice(warpAdapter
            , D3D_FEATURE_LEVEL_12_0
            , IID_PPV_ARGS(&device));
    }

    //  NOTE : create fence
    hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));

    rtvDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    dsvDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
    cbvDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    //  NOTE : create command allocator
    hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT
        , IID_PPV_ARGS(&commandAllocator));

    if (nullptr == commandAllocator)
    {
        return;
    }

    //  NOTE : create command list
    hr = device->CreateCommandList(0
        , D3D12_COMMAND_LIST_TYPE_DIRECT
        , commandAllocator
        , nullptr
        , IID_PPV_ARGS(&commandList));
    hr = commandList->Close();

    //  NOTE : create command queue
    D3D12_COMMAND_QUEUE_DESC commandQueueDesc = {};
    commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    hr = device->CreateCommandQueue(&commandQueueDesc
        , IID_PPV_ARGS(&commandQueue));

    //  NOTE : create swapchain
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferDesc.Width = window->Width();
    swapChainDesc.BufferDesc.Height = window->Height();
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.OutputWindow = reinterpret_cast<HWND>(window->PlatformHandle());
    swapChainDesc.Windowed = true;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    if (nullptr == commandQueue)
    {
        return;
    }
    hr = dxgiFactory->CreateSwapChain(commandQueue, &swapChainDesc, &swapChain);

    //  NOTE: create render target view heap
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
    rtvHeapDesc.NumDescriptors = 2;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    rtvHeapDesc.NodeMask = 0;
    hr = device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

    //  NOTE: create depth stencil view heap
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
    dsvHeapDesc.NumDescriptors = 1;
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    dsvHeapDesc.NodeMask = 0;
    hr = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

    //  NOTE: on resize
    OnResize();

    //  NOTE: create root signature
    CD3DX12_ROOT_PARAMETER slotRootParameter[1] = {};
    CD3DX12_DESCRIPTOR_RANGE cbvTable;
    cbvTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
    slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable);

    CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(1, slotRootParameter, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
    ID3DBlob* errors = nullptr;
    ID3DBlob* serializeRootSignature = nullptr;
    hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &serializeRootSignature, &errors);
    hr = device->CreateRootSignature(0, serializeRootSignature->GetBufferPointer(), serializeRootSignature->GetBufferSize(), IID_PPV_ARGS(&rootSignature));

    hr = D3DCompileFromFile(L"..\\Core\\Shaders\\BasicShader.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_0", 0, 0, &vsShaderByteCode, &errors);
    hr = D3DCompileFromFile(L"..\\Core\\Shaders\\BasicShader.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0", 0, 0, &psShaderByteCode, &errors);

    inputLayout =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };

    vertices.push_back({ DirectX::XMFLOAT3(-2.0f, -2.0f, 5.0f), DirectX::XMFLOAT4(DirectX::Colors::White) });
    vertices.push_back({ DirectX::XMFLOAT3(2.0f, -2.0f, 5.0f), DirectX::XMFLOAT4(DirectX::Colors::Black) });
    vertices.push_back({ DirectX::XMFLOAT3(2.0f, -2.0f, 5.0f), DirectX::XMFLOAT4(DirectX::Colors::Red) });

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    //  NOTE: create pipeline
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
    ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
    psoDesc.InputLayout = { inputLayout.data(), (UINT)inputLayout.size() };
    psoDesc.pRootSignature = rootSignature;
    psoDesc.VS =
    {
        reinterpret_cast<BYTE*>(vsShaderByteCode->GetBufferPointer()), vsShaderByteCode->GetBufferSize()
    };
    psoDesc.PS =
    {
        reinterpret_cast<BYTE*>(psShaderByteCode->GetBufferPointer()), psShaderByteCode->GetBufferSize()
    };
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.SampleDesc.Count = 1;
    psoDesc.SampleDesc.Quality = 0;
    psoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    hr = device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState));

    //  NOTE: create viewport
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = window->Width();
    viewport.Height = window->Height();
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    //  NOTE: create scissor rect
    scissorRect = { 0, 0, window->Width(), window->Height() };

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart());
    for (size_t i = 0; i < 2; i++)
    {
        swapChain->GetBuffer(i, IID_PPV_ARGS(&swapChainBuffer[i]));
        device->CreateRenderTargetView(swapChainBuffer[i], nullptr, rtvHeapHandle);
        rtvHeapHandle.Offset(1, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
    }

    //  NOTE: create desc heap
    D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
    cbvHeapDesc.NumDescriptors = 1;
    cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    cbvHeapDesc.NodeMask = 0;
    hr = device->CreateDescriptorHeap(&cbvHeapDesc, IID_PPV_ARGS(&cbvHeap));

    //  NOTE: create constant buffer
    UINT mElementByteSize = sizeof(ObjectConstants) + 255 & ~255;
    auto uploadProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    auto buffer = CD3DX12_RESOURCE_DESC::Buffer(mElementByteSize);
    hr = device->CreateCommittedResource(&uploadProp, D3D12_HEAP_FLAG_NONE, &buffer, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&uploadBuffer));
    uploadBuffer->Map(0, nullptr, reinterpret_cast<void**>(&mappedData));
    D3D12_GPU_VIRTUAL_ADDRESS cbAddr = uploadBuffer->GetGPUVirtualAddress();

    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
    cbvDesc.BufferLocation = cbAddr;
    cbvDesc.SizeInBytes = (sizeof(ObjectConstants) + 255) & ~255;

    device->CreateConstantBufferView(&cbvDesc, cbvHeap->GetCPUDescriptorHandleForHeapStart());

    //  NOTE: create vertex, index buffer
    vertexSize = (UINT)vertices.size() * sizeof(Vertex);
    hr = D3DCreateBlob(vertexSize, &vertexBufferCPU);
    CopyMemory(vertexBufferCPU->GetBufferPointer(), vertices.data(), vertexSize);

    indexSize = (UINT)indices.size() * sizeof(std::uint16_t);
    hr = D3DCreateBlob(indexSize, &indexBufferCPU);
    CopyMemory(indexBufferCPU->GetBufferPointer(), indices.data(), indexSize);

    vertexBufferGPU = CreateDefaultBuffer(vertices.data(), vertexSize, &vertexBufferUploader);
    indexBufferGPU = CreateDefaultBuffer(indices.data(), indexSize, &indexBufferUploader);
}

void Core::GraphicsDeviceContext::Update()
{
    XMMATRIX identity = XMMatrixIdentity();
    // Build the view matrix.
    XMVECTOR pos = XMVectorSet(0.0f, 0.0f, -5.0f, 1.0f);
    XMVECTOR target = XMVectorZero();
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
    XMFLOAT4X4 mView;
    XMStoreFloat4x4(&mView, view);

    XMFLOAT4X4 mWorld;
    XMMATRIX world = XMMatrixIdentity();

    XMMATRIX proj = XMMatrixPerspectiveFovLH(0.5f * XM_PIDIV4, 1024.0f / 768.0f, 1.0f, 1000.0f);
    XMMATRIX worldViewProj = world * view * proj;

    // Update the constant buffer with the latest worldViewProj matrix.
    ObjectConstants objConstants;
    XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
    memcpy(&mappedData[0], &objConstants, sizeof(ObjectConstants));
}

void Core::GraphicsDeviceContext::Render()
{
    HRESULT hr = S_OK;

    hr = commandAllocator->Reset();
    hr = commandList->Reset(commandAllocator, nullptr);

    auto transRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(
        swapChainBuffer[backbufferCount]
        , D3D12_RESOURCE_STATE_PRESENT
        , D3D12_RESOURCE_STATE_RENDER_TARGET);
    commandList->ResourceBarrier(1
        , &transRenderTarget);

    commandList->RSSetViewports(1, &viewport);
    commandList->RSSetScissorRects(1, &scissorRect);

    int handleSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    auto getRtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeap->GetCPUDescriptorHandleForHeapStart()
            , backbufferCount
            , handleSize);
    
    float color[4]{ 0.5f, 0.5f, 0.5f, 1.0f };
    commandList->ClearRenderTargetView(getRtvHandle, color, 0, nullptr);
    commandList->ClearDepthStencilView(dsvHeap->GetCPUDescriptorHandleForHeapStart()
        , D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL
        , 1.0f
        , 0, 0, nullptr);

    auto heapStart = dsvHeap->GetCPUDescriptorHandleForHeapStart();
    commandList->OMSetRenderTargets(1
        , &getRtvHandle
        , true
        , &heapStart);

    ID3D12DescriptorHeap* descHeap[] = { cbvHeap };
    commandList->SetDescriptorHeaps(_countof(descHeap), descHeap);

    commandList->SetGraphicsRootSignature(rootSignature);

    D3D12_VERTEX_BUFFER_VIEW vbv;
    vbv.BufferLocation = vertexBufferGPU->GetGPUVirtualAddress();
    vbv.StrideInBytes = sizeof(Vertex);
    vbv.SizeInBytes = vertexSize;
    commandList->IASetVertexBuffers(0, 1, &vbv);

    D3D12_INDEX_BUFFER_VIEW ibv;
    ibv.BufferLocation = indexBufferGPU->GetGPUVirtualAddress();
    ibv.Format = DXGI_FORMAT_R16_UINT;
    ibv.SizeInBytes = indexSize;
    commandList->IASetIndexBuffer(&ibv);

    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    commandList->SetGraphicsRootDescriptorTable(0, cbvHeap->GetGPUDescriptorHandleForHeapStart());
    commandList->DrawInstanced(3, 1, 0, 0);

    auto transPresent = CD3DX12_RESOURCE_BARRIER::Transition(
        swapChainBuffer[backbufferCount]
        , D3D12_RESOURCE_STATE_RENDER_TARGET
        , D3D12_RESOURCE_STATE_PRESENT);
    commandList->ResourceBarrier(1, &transPresent);

    hr = commandList->Close();

    ID3D12CommandList* cmdList[] = { commandList };
    commandQueue->ExecuteCommandLists(_countof(cmdList), cmdList);

    hr = swapChain->Present(0, 0);

    backbufferCount = (backbufferCount + 1) % 2;
    FlushCommandQueue();
}

void Core::GraphicsDeviceContext::FlushCommandQueue()
{
    currentFence++;
    HRESULT hr = commandQueue->Signal(fence, currentFence);

    if (fence->GetCompletedValue() < currentFence)
    {
        HANDLE eventHandle = CreateEventEx(nullptr, 0, 0, EVENT_ALL_ACCESS);
        hr = fence->SetEventOnCompletion(currentFence, eventHandle);

        auto signal = WaitForSingleObject(eventHandle, INFINITE);
        auto close = CloseHandle(eventHandle);
    }
}

void Core::GraphicsDeviceContext::OnResize()
{
    FlushCommandQueue();

    HRESULT hr = commandList->Reset(commandAllocator, nullptr);
    hr = swapChain->ResizeBuffers(2
        , window->Width(), window->Height()
        , DXGI_FORMAT_R8G8B8A8_UNORM
        , DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

    backbufferCount = 0;

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart());
    for (UINT i = 0; i < 2; i++)
    {
        hr = swapChain->GetBuffer(i, IID_PPV_ARGS(&swapChainBuffer[i]));
        device->CreateRenderTargetView(swapChainBuffer[i], nullptr, rtvHeapHandle);
        rtvHeapHandle.Offset(1, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
    }

    // Create the depth/stencil buffer and view.
    D3D12_RESOURCE_DESC depthStencilDesc;
    depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    depthStencilDesc.Alignment = 0;
    depthStencilDesc.Width = window->Width();
    depthStencilDesc.Height = window->Height();
    depthStencilDesc.DepthOrArraySize = 1;
    depthStencilDesc.MipLevels = 1;

    // Correction 11/12/2016: SSAO chapter requires an SRV to the depth buffer to read from 
    // the depth buffer.  Therefore, because we need to create two views to the same resource:
    //   1. SRV format: DXGI_FORMAT_R24_UNORM_X8_TYPELESS
    //   2. DSV Format: DXGI_FORMAT_D24_UNORM_S8_UINT
    // we need to create the depth buffer resource with a typeless format.  
    depthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;

    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

    D3D12_CLEAR_VALUE optClear;
    optClear.Format = mDepthStencilFormat;
    optClear.DepthStencil.Depth = 1.0f;
    optClear.DepthStencil.Stencil = 0;
    auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
    hr = device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &depthStencilDesc,
        D3D12_RESOURCE_STATE_COMMON,
        &optClear,
        IID_PPV_ARGS(&depthStencilBuffer));

    // Create descriptor to mip level 0 of entire resource using the format of the resource.
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
    dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
    dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    dsvDesc.Format = mDepthStencilFormat;
    dsvDesc.Texture2D.MipSlice = 0;
    device->CreateDepthStencilView(depthStencilBuffer, &dsvDesc, dsvHeap->GetCPUDescriptorHandleForHeapStart());

    // Transition the resource from its initial state to be used as a depth buffer.
    auto trans = CD3DX12_RESOURCE_BARRIER::Transition(depthStencilBuffer,
        D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE);
    commandList->ResourceBarrier(1, &trans);

    // Execute the resize commands.
    hr = commandList->Close();
    ID3D12CommandList* cmdsLists[] = { commandList };
    commandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

    // Wait until resize is complete.
    FlushCommandQueue();

    // Update the viewport transform to cover the client area.
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = static_cast<float>(window->Width());
    viewport.Height = static_cast<float>(window->Height());
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    scissorRect = { 0, 0, window->Width(), window->Height()};
}

ID3D12Resource* Core::GraphicsDeviceContext::CreateDefaultBuffer(const void* initData, unsigned int byteSize, ID3D12Resource** uploadBuffer)
{
    ID3D12Resource* defaultBuffer;
    D3D12_HEAP_PROPERTIES heapPropDefault = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
    D3D12_HEAP_PROPERTIES heapPropUpload = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

    auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(byteSize);
    device->CreateCommittedResource(
        &heapPropDefault
        , D3D12_HEAP_FLAG_NONE
        , &resourceDesc
        , D3D12_RESOURCE_STATE_COMMON
        , nullptr
        , IID_PPV_ARGS(&defaultBuffer));

    device->CreateCommittedResource(
        &heapPropUpload
        , D3D12_HEAP_FLAG_NONE
        , &resourceDesc
        , D3D12_RESOURCE_STATE_GENERIC_READ
        , nullptr
        , IID_PPV_ARGS(uploadBuffer));
    D3D12_SUBRESOURCE_DATA subResourceData = {};
    subResourceData.pData = initData;
    subResourceData.RowPitch = byteSize;
    subResourceData.SlicePitch = subResourceData.RowPitch;

    CD3DX12_RESOURCE_BARRIER transCopyDest = CD3DX12_RESOURCE_BARRIER::Transition(
        defaultBuffer
        , D3D12_RESOURCE_STATE_COMMON
        , D3D12_RESOURCE_STATE_COPY_DEST);
    commandList->ResourceBarrier(1, &transCopyDest);
    UpdateSubresources<1>(commandList
        , defaultBuffer
        , *uploadBuffer
        , 0, 0, 1, &subResourceData);

    auto transGenRead = CD3DX12_RESOURCE_BARRIER::Transition(
        defaultBuffer
        , D3D12_RESOURCE_STATE_COPY_DEST
        , D3D12_RESOURCE_STATE_GENERIC_READ);
    commandList->ResourceBarrier(1, &transGenRead);

    return defaultBuffer;
}
#endif // _WIN32
