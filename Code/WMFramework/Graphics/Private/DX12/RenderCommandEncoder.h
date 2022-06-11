#pragma once
#include "Graphics/WMRenderCommandEncoder.h"

namespace WildMini::Graphics::Private::DX12
{
    class RenderCommandEncoder : public WMRenderCommandEncoder
    {
    public:
        virtual void SetViewport(const Primitive::WMViewport& viewport) override;
        virtual void SetScissorRect(const Primitive::WMRect& rect) override;
        virtual void SetRenderTarget(const WMTexture* renderTarget) override;
        virtual void ClearRenderTarget(const WMTexture* renderTarget, const Primitive::WMColor& color) override;
    };
}
