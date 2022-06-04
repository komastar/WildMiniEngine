#ifdef _WIN32
#include "GraphicsDeviceContext.h"
#include "CommandList.h"
#include "CommandQueue.h"
#include "GPUBuffer.h"
#include "Texture.h"

using namespace WildMini::Object;
using namespace WildMini::Graphics;
using namespace WildMini::Graphics::Private;
using namespace WildMini::Graphics::Private::DX12;

GraphicsDeviceContext::GraphicsDeviceContext()
    : device(nullptr)
    , dxgiFactory(nullptr)
{
    CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
    D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device));
}

GraphicsDeviceContext::~GraphicsDeviceContext()
{
}

WMObject<WMCommandQueue> GraphicsDeviceContext::CreateCommandQueue()
{
    return new CommandQueue(device.Get());
}

WMObject<WMCommandList> GraphicsDeviceContext::CreateCommandList()
{
    ComPtr<ID3D12CommandAllocator> commandAllocator;
    device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
    return new CommandList(device.Get(), commandAllocator.Get());
}

WMObject<WMGPUBuffer> GraphicsDeviceContext::CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode)
{
    D3D12_HEAP_PROPERTIES heapProp = {};
    D3D12_RESOURCE_STATES initBufferState = {};

    switch (mode)
    {
    case WildMini::Graphics::WMGPUBuffer::NONE:
        heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        initBufferState = D3D12_RESOURCE_STATE_GENERIC_READ;
        break;
    case WildMini::Graphics::WMGPUBuffer::WRITABLE:
        heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        initBufferState = D3D12_RESOURCE_STATE_GENERIC_READ;
        break;
    case WildMini::Graphics::WMGPUBuffer::READABLE:
        heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_READBACK);
        initBufferState = D3D12_RESOURCE_STATE_COPY_DEST;
        break;
    }

    D3D12_RESOURCE_DESC desc = {};
    desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Alignment = 0;
    desc.Width = AlignGPUBufferSize(size);
    desc.Height = 1;
    desc.DepthOrArraySize = 1;
    desc.MipLevels = 1;
    desc.Format = DXGI_FORMAT_UNKNOWN;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    desc.Flags = D3D12_RESOURCE_FLAG_NONE;

    ComPtr<ID3D12Resource> buffer;
    device->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &desc, initBufferState, nullptr, IID_PPV_ARGS(buffer.GetAddressOf()));

    return new GPUBuffer(buffer.Get(), mode, initBufferState);
}

WMObject<WMTexture> GraphicsDeviceContext::CreateTexture(const WMTexture::Desc& desc)
{
    D3D12_RESOURCE_DESC bufferDesc = {};
    bufferDesc.Width = desc.width;
    bufferDesc.Height = desc.height;
    bufferDesc.DepthOrArraySize = desc.depth;
    bufferDesc.MipLevels = desc.mipLevels;
    bufferDesc.SampleDesc.Count = desc.sampleCount;
    bufferDesc.SampleDesc.Quality = 0;
    bufferDesc.Format = PixelFormat(desc.format);

    switch (desc.type)
    {
    case WMTexture::_1D:
        bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE1D;
        break;
    case WMTexture::_2D:
        bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        break;
    case WMTexture::_3D:
        bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D;
        break;
    }

    D3D12_RESOURCE_STATES initState = D3D12_RESOURCE_STATE_COMMON;
    bufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    if (desc.usage & WMTexture::USAGE_SHADER_READ)
    {
        initState = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
    }
    else
    {
        bufferDesc.Flags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
    }

    if (desc.usage & WMTexture::USAGE_RENDER_TARGET)
    {
        bufferDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
        initState = D3D12_RESOURCE_STATE_RENDER_TARGET;
    }

    if (desc.usage & WMTexture::USAGE_DEPTH_STENCIL)
    {
        bufferDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
        initState = D3D12_RESOURCE_STATE_DEPTH_WRITE;
    }

    ComPtr<ID3D12Resource> buffer;
    CD3DX12_HEAP_PROPERTIES heapProp(D3D12_HEAP_TYPE_DEFAULT);
    device->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &bufferDesc, initState, nullptr, IID_PPV_ARGS(buffer.GetAddressOf()));

    return new Texture(buffer.Get(), initState);
}
#endif // _WIN32
