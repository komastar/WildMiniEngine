//
//  File:   WMRenderPipeline.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMSharedPtr.h"
#include "Graphics/WMShader.h"
#include "Graphics/WMVertexDescriptor.h"
#include "Graphics/WMBlendState.h"
#include "Graphics/WMTexture.h"

namespace WildMini
{
    class WM_API WMRenderPipeline : public WMRefCounter
    {
    };

    enum class WMPrimitiveTopologyType
    {
        Point,
        Line,
        Triangle
    };

    struct WMRenderPipelineColorAttachmentDescriptor
    {
        WMPixelFormat pixelFormat = WMPixelFormat::RGBA_8_UNML;

        bool blendEnabled = true;

        WMBlendOperation rgbBlendOperation = WMBlendOperation::Add;
        WMBlendFactor srcRgbBlendFactor = WMBlendFactor::SrcAlpha;
        WMBlendFactor dstRgbBlendFactor = WMBlendFactor::OneMinusSrcAlpha;

        WMBlendOperation alphaBlendOperation = WMBlendOperation::Add;
        WMBlendFactor srcAlphaBlendFactor = WMBlendFactor::One;
        WMBlendFactor dstAlphaBlendFactor = WMBlendFactor::Zero;

        bool logicEnabled = false;
        WMLogicOperation logicOperation = WMLogicOperation::NOOP;

        WMColorWriteMask writeMask = WMColorWriteMask::ColorWriteMaskAll;
    };

    struct WMRenderPipelineDescriptor
    {
        uint32_t sampleCount;
        WMSharedPtr<WMShader> vertexShader;
        WMSharedPtr<WMShader> fragmentShader;

        WMVertexDescriptor vertexDescriptor;
        std::vector<WMRenderPipelineColorAttachmentDescriptor> colorAttachments;
        WMPixelFormat depthStencilPixelFormat;
        WMPrimitiveTopologyType inputPrimitiveTopology;
    };
}
