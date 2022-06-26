//
//  File:   WMVertexDescriptor.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"

namespace WildMini::Graphics
{
    enum class WMVertexFormat
    {
        Invalid = 0,
        Float,
        Float2,
        Float3,
        Float4
    };

    struct WMVertexAttributeDescriptor
    {
        WMVertexFormat format;
        const char* semanticName;
        uint32_t semanticIndex;
        uint32_t offset;
    };

    struct WMVertexDescriptor
    {
        std::vector<WMVertexAttributeDescriptor> attributes;
    };
}