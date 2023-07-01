//
//  File:   WMRenderCommandEncoder.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMContainer.h"
#include "WMSharedPtr.h"
#include "Graphics/Primitive/WMViewport.h"
#include "Graphics/WMTexture.h"
#include "Graphics/WMGPUBuffer.h"
#include "Graphics/Primitive/WMColor.h"

namespace WildMini
{
    class WM_API WMRenderCommandEncoder : public WMRefCounter
    {
    public:
        enum class DepthStencilClearFlag
        {
            Depth,
            Stencil,
            All
        };

        enum class PrimitiveType
        {
            Point,
            Line,
            LineStrip,
            Triangle,
            TriangleStrip
        };

    public:
        virtual void SetViewport(const WMViewport& viewport) = 0;
        virtual void SetViewports(const WMViewport* viewports, uint32_t count) = 0;
        virtual void SetScissorRect(const WMRect& rect) = 0;
        virtual void SetScissorRects(const WMRect* rect, uint32_t count) = 0;
        virtual void SetRenderTargets(Vector<const WMTexture*> renderTargets, const WMTexture* depthStencil) = 0;
        virtual void SetTexture(const WMTexture* texture, const uint32_t index = 0) = 0;
        virtual void ClearRenderTarget(const WMTexture* renderTarget, const WMColor& color) = 0;
        virtual void ClearDepthStencil(const WMTexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) = 0;
        virtual void SetConstantBuffer(uint32_t index, const WMGPUBuffer* constantBuffer) = 0;
        virtual void SetVertexBuffer(const WMGPUBuffer* vertexBuffer, const uint32_t vertexSize, const uint32_t slot = 0, const uint32_t numViews = 1) = 0;
        virtual void SetIndexBuffer(const WMGPUBuffer* indexBuffer) = 0;
        virtual void DrawPrimitives(PrimitiveType primitiveType, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t instanceStart) = 0;
        virtual void DrawPrimitivesIndexed(PrimitiveType primitiveType, uint32_t indexCount, uint32_t instanceCount = 1, uint32_t indexStart = 0, uint32_t startVertex = 0, uint32_t instanceStart = 0) = 0;
        
        virtual void ImguiRender() = 0;

        virtual void EndEncoding(Vector<const WMTexture*> renderTargets) = 0;
    };
}
