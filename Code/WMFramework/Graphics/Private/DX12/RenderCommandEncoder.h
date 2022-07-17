//
//  File:   RenderCommandEncoder.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "d3d12_include.h"
#include "Graphics/WMRenderCommandEncoder.h"
#include "CommandBuffer.h"
#include "RenderPipeline.h"
#include "Graphics/WMGPUBuffer.h"

namespace WildMini::Graphics::Private::DX12
{
    class RenderCommandEncoder : public WMRenderCommandEncoder
    {
    public:
        RenderCommandEncoder(RenderPipeline* _renderPipeline, WMCommandBuffer* _commandBuffer, ID3D12GraphicsCommandList* _commandList);
        ~RenderCommandEncoder();

    public:
        virtual void SetViewport(const Primitive::WMViewport& viewport) override;
        virtual void SetScissorRect(const Primitive::WMRect& rect) override;
        virtual void ClearRenderTarget(const WMTexture* renderTarget, const Primitive::WMColor& color) override;
        virtual void SetViewports(const Primitive::WMViewport* viewports, uint32_t count) override;
        virtual void SetScissorRects(const Primitive::WMRect* rects, uint32_t count) override;
        virtual void SetRenderTargets(std::vector<const WMTexture*> renderTargets, const WMTexture* depthStencil) override;
        virtual void ClearDepthStencil(const WMTexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) override;
        virtual void SetConstantBuffer(uint32_t index, const WMGPUBuffer* constantBuffer) override;
        virtual void SetVertexBuffer(const WMGPUBuffer* vertexBuffer, uint32_t vertexSize) override;
        virtual void DrawPrimitives(PrimitiveType primitiveType, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t instanceStart);
        virtual void EndEncoding() override;

    private:
        void TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before);
        void SetPrimitiveType(PrimitiveType primitiveType);

    protected:
        ComPtr<ID3D12GraphicsCommandList> commandList;
        Object::WMObject<WMCommandBuffer> commandBuffer;
    };
}
