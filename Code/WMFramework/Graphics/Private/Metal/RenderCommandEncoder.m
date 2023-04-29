//
//  RenderCommandEncoder.m
//  WMFramework
//
//  Created by Eugene Kim on 2023/04/29.
//

#import <Foundation/Foundation.h>
#include "Graphics/Private/Metal/RenderCommandEncoder.h"

using namespace WildMini;

RenderCommandEncoder::RenderCommandEncoder()

{
}

RenderCommandEncoder::~RenderCommandEncoder()
{
}

void RenderCommandEncoder::SetViewport(const WMViewport& viewport)
{
}

void RenderCommandEncoder::SetViewports(const WMViewport* viewports, uint32_t count)
{
}

void RenderCommandEncoder::SetScissorRects(const WMRect* rect, uint32_t count)
{

}


void RenderCommandEncoder::SetScissorRect(const WMRect& rect)
{

}

void RenderCommandEncoder::ClearRenderTarget(const WMTexture* renderTarget, const WMColor &color)
{
}

void RenderCommandEncoder::ClearDepthStencil(const WMTexture* depthStencil, WMRenderCommandEncoder::DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil)
{
}

void RenderCommandEncoder::SetConstantBuffer(uint32_t index, const WMGPUBuffer *constantBuffer)
{

}

void RenderCommandEncoder::SetVertexBuffer(const WMGPUBuffer* vertexBuffer, const uint32_t vertexSize, const uint32_t slot, const uint32_t numViews)
{

}

void RenderCommandEncoder::SetIndexBuffer(const WMGPUBuffer *indexBuffer)
{
}

void RenderCommandEncoder::DrawPrimitivesIndexed(WMRenderCommandEncoder::PrimitiveType primitiveType, uint32_t indexCount, uint32_t instanceCount, uint32_t indexStart, uint32_t startVertex, uint32_t instanceStart)
{
}

void RenderCommandEncoder::DrawPrimitives(WMRenderCommandEncoder::PrimitiveType primitiveType, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t instanceStart)
{
}

void RenderCommandEncoder::EndEncoding(Vector<const WMTexture*> renderTargets)
{
}


void RenderCommandEncoder::ImguiRender()
{

}

void RenderCommandEncoder::SetRenderTargets(Vector<const WMTexture*> renderTargets, const WMTexture* depthStencil)
{
}
