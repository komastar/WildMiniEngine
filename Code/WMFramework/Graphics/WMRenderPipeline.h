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

        WMBlendOperation
    };

    struct WMRenderPipelineDescriptor
    {
        uint32_t sampleCount;
        WildMini::Object::WMObject<WildMini::Graphics::WMShader> vertexShader;
        WildMini::Object::WMObject<WildMini::Graphics::WMShader> fragmentShader;

        WMVertexDescriptor vertexDescriptor;

    };
}
