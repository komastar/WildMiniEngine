#pragma once
#include "Graphics/WMRenderCommandEncoder.h"

namespace WildMini::Graphics::Private::DX12
{
    class RenderCommandEncoder : public WMRenderCommandEncoder
    {
    public:
        virtual void SetViewport() override;
        virtual void SetScissorRect() override;
        virtual void SetRenderTarget() override;
        virtual void ClearRenderTarget() override;
    };
}
