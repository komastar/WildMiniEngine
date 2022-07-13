//
//  File:   GraphicsDeviceContext.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#ifdef _WIN32
#include "GraphicsDeviceContext.h"
#include "CommandQueue.h"
#include "GPUBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "Type.h"
#include "RenderPipeline.h"

using namespace WildMini::Object;
using namespace WildMini::Graphics;
using namespace WildMini::Graphics::Private;
using namespace WildMini::Graphics::Private::DX12;

static std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSampler()
{
    const CD3DX12_STATIC_SAMPLER_DESC pointWrap(
        0,
        D3D12_FILTER_MIN_MAG_MIP_POINT,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP
    );

    const CD3DX12_STATIC_SAMPLER_DESC pointClamp(
        1,
        D3D12_FILTER_MIN_MAG_MIP_POINT,
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP
    );

    const CD3DX12_STATIC_SAMPLER_DESC linearWrap(
        2,
        D3D12_FILTER_MIN_MAG_MIP_LINEAR,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP
    );

    const CD3DX12_STATIC_SAMPLER_DESC linearClamp(
        3,
        D3D12_FILTER_MIN_MAG_MIP_LINEAR,
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP
    );

    const CD3DX12_STATIC_SAMPLER_DESC anisotropicWrap(
        4,
        D3D12_FILTER_ANISOTROPIC,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        0.0f,
        8
    );

    const CD3DX12_STATIC_SAMPLER_DESC anisotropicClamp(
        5,
        D3D12_FILTER_ANISOTROPIC,
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
        0.0f,
        0
    );

    return {
        pointWrap, pointClamp, linearWrap, linearClamp, anisotropicWrap, anisotropicClamp
    };
}

GraphicsDeviceContext::GraphicsDeviceContext()
    : device(nullptr)
    , dxgiFactory(nullptr)
{
#if defined(DEBUG) || defined(_DEBUG) 
    {
        ComPtr<ID3D12Debug> debugController;
        D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
        debugController->EnableDebugLayer();
    }
#endif
    CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
    D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device));
}

GraphicsDeviceContext::~GraphicsDeviceContext()
{
}

WMObject<WMCommandQueue> GraphicsDeviceContext::CreateCommandQueue()
{
    ComPtr<ID3D12CommandQueue> commandQueue;
    D3D12_COMMAND_QUEUE_DESC commandQueueDesc = {};
    commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));

    ComPtr<ID3D12Fence> fence;
    device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));

    ComPtr<ID3D12CommandAllocator> commandAllocator;
    device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));

    ComPtr<ID3D12GraphicsCommandList> commandList;
    device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList));
    commandList->Close();

    return new CommandQueue(this, commandQueue.Get(), commandAllocator.Get(), commandList.Get(), fence.Get());
}

WMObject<WMGPUBuffer> GraphicsDeviceContext::CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode)
{
    D3D12_HEAP_PROPERTIES heapProp = {};
    D3D12_RESOURCE_STATES initBufferState = {};

    switch (mode)
    {
    case WildMini::Graphics::WMGPUBuffer::CPUCacheMode::NONE:
        heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        initBufferState = D3D12_RESOURCE_STATE_GENERIC_READ;
        break;
    case WildMini::Graphics::WMGPUBuffer::CPUCacheMode::WRITABLE:
        heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        initBufferState = D3D12_RESOURCE_STATE_GENERIC_READ;
        break;
    case WildMini::Graphics::WMGPUBuffer::CPUCacheMode::READABLE:
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
    bufferDesc.Format = FromPixelFormat(desc.format);

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

WMObject<WMRenderPipeline> GraphicsDeviceContext::CreateRenderPipeline(const WMRenderPipelineDescriptor& desc)
{
    ComPtr<ID3D12RootSignature> rootSignature;
    CD3DX12_ROOT_PARAMETER slotRootParams[1] = {};
    slotRootParams[0].InitAsConstantBufferView(0);

    auto staticSamplers = GetStaticSampler();

    CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(
        1
        , slotRootParams
        , static_cast<UINT>(staticSamplers.size())
        , staticSamplers.data()
        , D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ComPtr<ID3DBlob> serializeRootSig = nullptr;
    ComPtr<ID3DBlob> errorBlob= nullptr;
    D3D12SerializeRootSignature(
        &rootSigDesc
        , D3D_ROOT_SIGNATURE_VERSION_1
        , serializeRootSig.GetAddressOf()
        , errorBlob.GetAddressOf());

    if (errorBlob)
    {
        ::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
    }

    device->CreateRootSignature(
        0
        , serializeRootSig->GetBufferPointer()
        , serializeRootSig->GetBufferSize()
        , IID_PPV_ARGS(&rootSignature));

    ComPtr<ID3D12PipelineState> pipelineState;
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.pRootSignature = rootSignature.Get();

    std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;
    inputLayout.reserve(desc.vertexDescriptor.attributes.size());
    for (const auto& attribute : desc.vertexDescriptor.attributes)
    {
        D3D12_INPUT_ELEMENT_DESC desc = {};
        desc.SemanticName = attribute.semanticName;
        desc.SemanticIndex = attribute.semanticIndex;
        desc.Format = FromVertexFormat(attribute.format);
        desc.AlignedByteOffset = attribute.offset;
        inputLayout.push_back(desc);
    }

    psoDesc.InputLayout = { inputLayout.data(), static_cast<UINT>(inputLayout.size()) };
    psoDesc.VS = const_cast<WMObject<WMShader>&>(desc.vertexShader).DynamicCast<Shader>()->ByteCode();
    psoDesc.PS = const_cast<WMObject<WMShader>&>(desc.fragmentShader).DynamicCast<Shader>()->ByteCode();
    psoDesc.PrimitiveTopologyType = PrimitiveType(desc.inputPrimitiveTopology);
    psoDesc.NumRenderTargets = static_cast<ULONG>(desc.colorAttachments.size());
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    for (int i = 0; i < desc.colorAttachments.size(); ++i)
    {
        const auto& attachment = desc.colorAttachments[i];
        psoDesc.RTVFormats[i] = FromPixelFormat(attachment.pixelFormat);
        psoDesc.BlendState.RenderTarget[i].BlendEnable = attachment.blendEnabled;
        psoDesc.BlendState.RenderTarget[i].BlendOp = FromBlendOperation(attachment.rgbBlendOperation);
        psoDesc.BlendState.RenderTarget[i].SrcBlend = FromBlendFactor(attachment.srcRgbBlendFactor);
        psoDesc.BlendState.RenderTarget[i].DestBlend = FromBlendFactor(attachment.dstRgbBlendFactor);
        psoDesc.BlendState.RenderTarget[i].BlendOpAlpha = FromBlendOperation(attachment.alphaBlendOperation);
        psoDesc.BlendState.RenderTarget[i].SrcBlendAlpha = FromBlendFactor(attachment.srcAlphaBlendFactor);
        psoDesc.BlendState.RenderTarget[i].DestBlendAlpha = FromBlendFactor(attachment.srcAlphaBlendFactor);
        psoDesc.BlendState.RenderTarget[i].RenderTargetWriteMask = attachment.writeMask;
    }

    psoDesc.SampleDesc.Count = desc.sampleCount;
    psoDesc.DSVFormat = FromPixelFormat(desc.depthStencilPixelFormat);
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    psoDesc.SampleMask = UINT_MAX;
    device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState));

    return new RenderPipeline(pipelineState.Get(), rootSignature.Get());
}

WMObject<WMShader> GraphicsDeviceContext::CreateShader(const std::vector<uint8_t>& data, const std::string& entry, WMShader::StageType stage)
{
    std::string shaderVerName;
    switch (stage)
    {
    case WMShader::StageType::Vertex:
        shaderVerName = "vs_5_1";
        break;
    case WMShader::StageType::Fragment:
        shaderVerName = "ps_5_1";
        break;
    default:
        WMASSERT_DESC(false, "Unsupported shader stage");
    }

    UINT compileFlags = 0;
    ComPtr<ID3DBlob> byteCode;
    ComPtr<ID3DBlob> errors;
    D3DCompile2(data.data(), data.size(), nullptr, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), shaderVerName.c_str(), compileFlags, 0, 0, 0, 0, &byteCode, &errors);

    return new Shader(byteCode.Get(), stage, entry);
}
#endif // _WIN32
