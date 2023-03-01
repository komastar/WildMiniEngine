//
//  File:   WMCopyCommandEncoder.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMRefCounter.h"
#include "Graphics/WMGPUBuffer.h"
#include "Graphics/WMTexture.h"

namespace WildMini
{
    class WM_API WMCopyCommandEncoder : public WMRefCounter
    {
    public:
        struct TextureArea
        {
            uint32_t x;
            uint32_t y;
            uint32_t width;
            uint32_t height;
        };

        virtual void CopyBufferToBuffer(WMGPUBuffer* src, size_t srcOffset, WMGPUBuffer* dest, size_t destOffset, size_t copySize) = 0;
        virtual void CopyBufferToTexture(WMGPUBuffer* src, size_t srcOffset, WMTexture* dest, TextureArea destArea) = 0;
        virtual void CopyTextureToBuffer(WMTexture* src, TextureArea srcArea, WMGPUBuffer* dest, size_t destOffset) = 0;
        virtual void EndEncoding() = 0;
    };
}
