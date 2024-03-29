//
//  File:   RenderCommandEncoder.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "d3d12_include.h"
#include "Graphics/WMRenderCommandEncoder.h"
#include "WMContainer.h"
#include "CommandBuffer.h"
#include "RenderPipeline.h"
#include "Graphics/WMGPUBuffer.h"

namespace WildMini
{
    class RenderCommandEncoder : public WMRenderCommandEncoder
    {
    public:
        RenderCommandEncoder(RenderPipeline* _renderPipeline, WMCommandBuffer* _commandBuffer, ID3D12GraphicsCommandList* _commandList);
        virtual ~RenderCommandEncoder();

    public:
        virtual void SetViewport(const WMViewport& viewport) override;
        virtual void SetScissorRect(const WMRect& rect) override;
        virtual void ClearRenderTarget(const WMTexture* renderTarget, const WMColor& color) override;
        virtual void SetViewports(const WMViewport* viewports, uint32_t count) override;
        virtual void SetScissorRects(const WMRect* rects, uint32_t count) override;
        virtual void SetRenderTargets(Vector<const WMTexture*> renderTargets, const WMTexture* depthStencil) override;
        virtual void ClearDepthStencil(const WMTexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) override;
        virtual void SetConstantBuffer(uint32_t index, const WMGPUBuffer* constantBuffer) override;
        virtual void SetTexture(const WMTexture* texture, const uint32_t index = 0) override;
        virtual void SetVertexBuffer(const WMGPUBuffer* vertexBuffer, const uint32_t vertexSize, const uint32_t slot = 0, const uint32_t numViews = 1) override;
        virtual void SetIndexBuffer(const WMGPUBuffer* indexBuffer) override;
        virtual void DrawPrimitives(PrimitiveType primitiveType, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t instanceStart);
        virtual void DrawPrimitivesIndexed(PrimitiveType primitiveType, uint32_t indexCount, uint32_t instanceCount = 1, uint32_t indexStart = 0, uint32_t startVertex = 0, uint32_t instanceStart = 0);
        virtual void ImguiRender() override;
        virtual void EndEncoding(Vector<const WMTexture*> renderTargets) override;

    private:
        void TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before);
        void SetPrimitiveType(PrimitiveType primitiveType);

    protected:
        ComPtr<ID3D12GraphicsCommandList> commandList;
        WMSharedPtr<WMCommandBuffer> commandBuffer;

        std::vector<const WMTexture*> renderTargetsTemp;
    };
}
