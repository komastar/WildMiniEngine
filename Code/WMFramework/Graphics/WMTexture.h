//
//  File:   WMTexture.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Object/WMObject.h"

namespace WildMini::Graphics
{
    enum WMPixelFormat
    {
        NONE = 0,

        RGBA_8_UNML,
        RGBA_8_SNML,
        RGBA_8_UINT,
        RGBA_8_SINT,

        DEPTH_24_UNORM_STENCIL_8
    };

    class WM_API WMTexture : public WildMini::Object::WMRefCounter
    {
    public:
        enum Type
        {
            _1D,
            _2D,
            _3D
        };

        enum Usage : uint32_t
        {
            USAGE_NONE = 0U,
            USAGE_SHADER_READ = 1U,
            USAGE_RENDER_TARGET = 1U << 1,
            USAGE_DEPTH_STENCIL = 1U << 2
        };

        struct Desc
        {
            WMTexture::Type type;
            WMPixelFormat format;
            uint32_t width;
            uint32_t height;
            uint32_t depth;
            uint32_t mipLevels;
            uint32_t sampleCount;
            uint32_t usage;
        };

    public:
        virtual size_t Size() const = 0;
        virtual uint32_t Width() const = 0;
        virtual uint32_t Height() const = 0;
        virtual WMPixelFormat Format() const = 0;
    };
}
