#include "RenderCommandEncoder.h"

using namespace WildMini::Graphics::Private::DX12;
using namespace WildMini::Graphics::Primitive;

RenderCommandEncoder::RenderCommandEncoder(WMCommandList* _commandList)
    : commandList(_commandList)
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
