//
//  File:   WMRenderCommandEncoder.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Object/WMObject.h"
#include "Graphics/Primitive/WMViewport.h"
#include "Graphics/WMTexture.h"
#include "Graphics/Primitive/WMColor.h"

namespace WildMini::Graphics
{
    class WM_API WMRenderCommandEncoder : public WildMini::Object::WMRefCounter
    {
    public:
        enum class DepthStencilClearFlag
        {
            Depth,
            Stencil,
            All
        };

    public:
        virtual void SetViewport(const Primitive::WMViewport& viewport) = 0;
        virtual void SetViewports(const Primitive::WMViewport* viewports, uint32_t count) = 0;
        virtual void SetScissorRect(const Primitive::WMRect& rect) = 0;
        virtual void SetScissorRects(const Primitive::WMRect* rect, uint32_t count) = 0;
        virtual void SetRenderTargets(std::vector<const WMTexture*> renderTargets, const WMTexture* depthStencil) = 0;
        virtual void ClearRenderTarget(const WMTexture* renderTarget, const Primitive::WMColor& color) = 0;
        virtual void ClearDepthStencil(const WMTexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) = 0;
        virtual void EndEncoding() = 0;
    };
}
