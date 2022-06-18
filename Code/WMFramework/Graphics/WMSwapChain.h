//
//  File:   WMSwapChain.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Object/WMObject.h"
#include "Graphics/WMTexture.h"

namespace WildMini::Graphics
{
    class WM_API WMSwapChain : public WildMini::Object::WMRefCounter
    {
    public:
        virtual const WMTexture* RenderTargetTexture() const = 0;
        virtual const WMTexture* DepthStencilTexture() const = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;
        virtual void Present() = 0;
    };
}
