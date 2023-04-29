//
//  RenderCommandEncoder.h
//  WMFramework
//
//  Created by Eugene Kim on 2023/04/29.
//

#ifdef __APPLE__
#ifndef RenderCommandEncoder_h
#define RenderCommandEncoder_h
#import <Metal/Metal.h>
#include "Graphics/WMRenderCommandEncoder.h"

namespace WildMini
{
    class RenderCommandEncoder : public WMRenderCommandEncoder
    {
    public:
        RenderCommandEncoder();
        ~RenderCommandEncoder();

    public:
        virtual void SetViewport(const WMViewport& viewport) override;
        virtual void SetViewports(const WMViewport* viewports, uint32_t count) override;
        virtual void SetScissorRect(const WMRect& rect) override;
        virtual void SetScissorRects(const WMRect* rect, uint32_t count) override;
        virtual void SetRenderTargets(Vector<const WMTexture*> renderTargets, const WMTexture* depthStencil) override;
        virtual void ClearRenderTarget(const WMTexture* renderTarget, const WMColor& color) override;
        virtual void ClearDepthStencil(const WMTexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) override;
        virtual void SetConstantBuffer(uint32_t index, const WMGPUBuffer* constantBuffer) override;
        virtual void SetVertexBuffer(const WMGPUBuffer* vertexBuffer, const uint32_t vertexSize, const uint32_t slot = 0, const uint32_t numViews = 1) override;
        virtual void SetIndexBuffer(const WMGPUBuffer* indexBuffer) override;
        virtual void DrawPrimitives(PrimitiveType primitiveType, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t instanceStart) override;
        virtual void DrawPrimitivesIndexed(PrimitiveType primitiveType, uint32_t indexCount, uint32_t instanceCount = 1, uint32_t indexStart = 0, uint32_t startVertex = 0, uint32_t instanceStart = 0) override;
        virtual void ImguiRender() override;
        virtual void EndEncoding(Vector<const WMTexture*> renderTargets) override;
    };
}

#endif /* RenderCommandEncoder_h */
#endif /* __APPLE__ */
