//
//  File:   Type.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "d3d12_include.h"
#include "Graphics/WMTexture.h"
#include "Graphics/WMRenderPipeline.h"
#include "Graphics/WMBlendState.h"
#include "Graphics/WMVertexDescriptor.h"

namespace WildMini::Graphics::Private::DX12
{
    using PixelFormat = WildMini::Graphics::WMPixelFormat;
    inline uint32_t PixelFormatSize(PixelFormat format)
    {
        switch (format)
        {
        case WildMini::Graphics::RGBA_8_UNML:
        case WildMini::Graphics::RGBA_8_SNML:
        case WildMini::Graphics::RGBA_8_UINT:
        case WildMini::Graphics::RGBA_8_SINT:
        case WildMini::Graphics::DEPTH_24_UNORM_STENCIL_8:
            return 4;
        default:
            break;
        }

        return 0;
    }

    inline PixelFormat ToPixelFormat(DXGI_FORMAT format)
    {
        switch (format)
        {
        case DXGI_FORMAT_R8G8B8A8_UNORM:
            return WildMini::Graphics::WMPixelFormat::RGBA_8_UNML;
        case DXGI_FORMAT_R8G8B8A8_SNORM:
            return WildMini::Graphics::WMPixelFormat::RGBA_8_SNML;
        case DXGI_FORMAT_R8G8B8A8_UINT:
            return WildMini::Graphics::WMPixelFormat::RGBA_8_UINT;
        case DXGI_FORMAT_R8G8B8A8_SINT:
            return WildMini::Graphics::WMPixelFormat::RGBA_8_SINT;
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
            return WildMini::Graphics::WMPixelFormat::DEPTH_24_UNORM_STENCIL_8;
        }

        return WMPixelFormat::NONE;
    }

    inline DXGI_FORMAT FromPixelFormat(PixelFormat format)
    {
        switch (format)
        {
        case WMPixelFormat::RGBA_8_UNML:
            return DXGI_FORMAT_R8G8B8A8_UNORM;
        case WMPixelFormat::RGBA_8_SNML:
            return DXGI_FORMAT_R8G8B8A8_SNORM;
        case WMPixelFormat::RGBA_8_UINT:
            return DXGI_FORMAT_R8G8B8A8_UINT;
        case WMPixelFormat::RGBA_8_SINT:
            return DXGI_FORMAT_R8G8B8A8_SINT;
        case WMPixelFormat::DEPTH_24_UNORM_STENCIL_8:
            return DXGI_FORMAT_D24_UNORM_S8_UINT;
        }

        return DXGI_FORMAT_UNKNOWN;
    }

    using VertexFormat = WildMini::Graphics::WMVertexFormat;
    inline DXGI_FORMAT FromVertexFormat(VertexFormat format)
    {
        switch (format)
        {
        case VertexFormat::Float:
            return DXGI_FORMAT_D32_FLOAT;
        case VertexFormat::Float2:
            return DXGI_FORMAT_R32G32_FLOAT;
        case VertexFormat::Float3:
            return DXGI_FORMAT_R32G32B32_FLOAT;
        case VertexFormat::Float4:
            return DXGI_FORMAT_R32G32B32A32_FLOAT;
        }
        return DXGI_FORMAT_UNKNOWN;
    }

    using PrimitiveTopology = WildMini::Graphics::WMPrimitiveTopologyType;
    inline D3D12_PRIMITIVE_TOPOLOGY_TYPE PrimitiveType(WMPrimitiveTopologyType type)
    {
        switch (type)
        {
        case WMPrimitiveTopologyType::Point:
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
        case WMPrimitiveTopologyType::Line:
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
        case WMPrimitiveTopologyType::Triangle:
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        }
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
    }

    using BlendOperation = WildMini::Graphics::WMBlendOperation;
    inline D3D12_BLEND_OP FromBlendOperation(BlendOperation blendOp)
    {
        switch (blendOp)
        {
        case BlendOperation::Add:
            return D3D12_BLEND_OP_ADD;
        case BlendOperation::Substract:
            return D3D12_BLEND_OP_SUBTRACT;
        case BlendOperation::ReserveSubtract:
            return D3D12_BLEND_OP_REV_SUBTRACT;
        case BlendOperation::Min:
            return D3D12_BLEND_OP_MIN;
        case BlendOperation::Max:
            return D3D12_BLEND_OP_MAX;
        default:
            break;
        }
        return D3D12_BLEND_OP_ADD;
    }

    using BlendFactor = WildMini::Graphics::WMBlendFactor;
    inline D3D12_BLEND FromBlendFactor(BlendFactor blendFactor)
    {
        switch (blendFactor)
        {
        case BlendFactor::Zero:
            return D3D12_BLEND_ZERO;
        case BlendFactor::One:
            return D3D12_BLEND_ONE;
        case BlendFactor::SrcColor:
            return D3D12_BLEND_SRC_COLOR;
        case BlendFactor::OneMinusSrcColor:
            return D3D12_BLEND_INV_SRC_COLOR;
        case BlendFactor::SrcAlpha:
            return D3D12_BLEND_SRC_ALPHA;
        case BlendFactor::OnMinusSrcAlpha:
            return D3D12_BLEND_INV_SRC_ALPHA;
        case BlendFactor::DstColor:
            return D3D12_BLEND_DEST_COLOR;
        case BlendFactor::OneMinusDstColor:
            return D3D12_BLEND_INV_DEST_COLOR;
        case BlendFactor::DstAlpha:
            return D3D12_BLEND_DEST_ALPHA;
        case BlendFactor::OneMinusDstAlpha:
            return D3D12_BLEND_INV_DEST_ALPHA;
        case BlendFactor::SrcAlphaSaturated:
            return D3D12_BLEND_SRC_ALPHA_SAT;
        case BlendFactor::BlendFactor:
            return D3D12_BLEND_BLEND_FACTOR;
        case BlendFactor::OneMinusBlendFactor:
            return D3D12_BLEND_INV_BLEND_FACTOR;
        default:
            break;
        }
        return D3D12_BLEND_ONE;
    }
}
