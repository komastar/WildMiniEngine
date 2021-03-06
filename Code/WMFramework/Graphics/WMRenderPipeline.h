//
//  File:   WMRenderPipeline.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Object/WMObject.h"
#include "Graphics/WMShader.h"
#include "Graphics/WMVertexDescriptor.h"
#include "Graphics/WMBlendState.h"
#include "Graphics/WMTexture.h"

namespace WildMini::Graphics
{
    class WM_API WMRenderPipeline : public Object::WMRefCounter
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
        WMPixelFormat pixelFormat;

        bool blendEnabled;

        WMBlendOperation alphaBlendOperation;
        WMBlendFactor srcAlphaBlendFactor;
        WMBlendFactor dstAlphaBlendFactor;

        WMBlendOperation rgbBlendOperation;
        WMBlendFactor srcRgbBlendFactor;
        WMBlendFactor dstRgbBlendFactor;

        WMColorWriteMask writeMask = WMColorWriteMask::ColorWriteMaskAll;
    };

    struct WMRenderPipelineDescriptor
    {
        uint32_t sampleCount;
        WildMini::Object::WMObject<WildMini::Graphics::WMShader> vertexShader;
        WildMini::Object::WMObject<WildMini::Graphics::WMShader> fragmentShader;

        WMVertexDescriptor vertexDescriptor;
        std::vector<WMRenderPipelineColorAttachmentDescriptor> colorAttachments;
        WMPixelFormat depthStencilPixelFormat;
        WMPrimitiveTopologyType inputPrimitiveTopology;
    };
}
