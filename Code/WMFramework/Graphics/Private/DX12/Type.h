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

namespace WildMini
{
    using PixelFormat = WMPixelFormat;
    inline uint32_t PixelFormatSize(PixelFormat format)
    {
        switch (format)
        {
        case PixelFormat::RGBA_8_UNML:
        case PixelFormat::RGBA_8_SNML:
        case PixelFormat::RGBA_8_UINT:
        case PixelFormat::RGBA_8_SINT:
        case PixelFormat::DEPTH_24_UNORM_STENCIL_8:
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
            return WMPixelFormat::RGBA_8_UNML;
        case DXGI_FORMAT_R8G8B8A8_SNORM:
            return WMPixelFormat::RGBA_8_SNML;
        case DXGI_FORMAT_R8G8B8A8_UINT:
            return WMPixelFormat::RGBA_8_UINT;
        case DXGI_FORMAT_R8G8B8A8_SINT:
            return WMPixelFormat::RGBA_8_SINT;
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
            return WMPixelFormat::DEPTH_24_UNORM_STENCIL_8;
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

    using VertexFormat = WMVertexFormat;
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
        case VertexFormat::Uint:
            return DXGI_FORMAT_R32_UINT;
        }
        return DXGI_FORMAT_UNKNOWN;
    }

    using PrimitiveTopology = WMPrimitiveTopologyType;
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

    using BlendOperation = WMBlendOperation;
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

    using LogicOperation = WMLogicOperation;
    inline D3D12_LOGIC_OP FromLogicOperation(LogicOperation logicOp)
    {
        switch (logicOp)
        {
        case LogicOperation::CLEAR:
            return D3D12_LOGIC_OP_CLEAR;
        case LogicOperation::SET:
            return D3D12_LOGIC_OP_SET;
        case LogicOperation::COPY:
            return D3D12_LOGIC_OP_COPY;
        case LogicOperation::COPY_INVERTED:
            return D3D12_LOGIC_OP_COPY_INVERTED;
        case LogicOperation::NOOP:
            return D3D12_LOGIC_OP_NOOP;
        case LogicOperation::INVERT:
            return D3D12_LOGIC_OP_INVERT;
        case LogicOperation::AND:
            return D3D12_LOGIC_OP_AND;
        case LogicOperation::NAND:
            return D3D12_LOGIC_OP_NAND;
        case LogicOperation::OR:
            return D3D12_LOGIC_OP_OR;
        case LogicOperation::NOR:
            return D3D12_LOGIC_OP_NOR;
        case LogicOperation::XOR:
            return D3D12_LOGIC_OP_XOR;
        case LogicOperation::EQUIV:
            return D3D12_LOGIC_OP_EQUIV;
        case LogicOperation::AND_REVERSE:
            return D3D12_LOGIC_OP_AND_REVERSE;
        case LogicOperation::AND_INVERTED:
            return D3D12_LOGIC_OP_AND_INVERTED;
        case LogicOperation::OR_REVERSE:
            return D3D12_LOGIC_OP_OR_REVERSE;
        case LogicOperation::OR_INVERTED:
            return D3D12_LOGIC_OP_OR_INVERTED;
        default:
            return D3D12_LOGIC_OP_NOOP;
        }
    }

    using BlendFactor = WMBlendFactor;
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
        case BlendFactor::OneMinusSrcAlpha:
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
