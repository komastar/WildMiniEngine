#include "RenderCommandEncoder.h"

using namespace WildMini::Graphics::Private::DX12;
using namespace WildMini::Graphics::Primitive;

RenderCommandEncoder::RenderCommandEncoder(WMRenderPipeline* _renderPipeline, WMCommandBuffer* _commandBuffer, WMCommandList* _commandList)
    : commandList(_commandList)
    , renderPipeline(_renderPipeline)
    , commandBuffer(_commandBuffer)
{
}

void RenderCommandEncoder::SetViewport(const WMViewport& viewport)
{
    commandList->SetViewport(viewport);
}

void RenderCommandEncoder::SetScissorRect(const WMRect& rect)
{
    commandList->SetScissorRect(rect);
}

void RenderCommandEncoder::SetRenderTarget(const WMTexture* renderTarget)
{
    commandList->SetRenderTarget(renderTarget);
}

void RenderCommandEncoder::ClearRenderTarget(const WMTexture* renderTarget, const WMColor& color)
{
    commandList->ClearRenderTarget(renderTarget, color);
}
