#pragma once
#include "Object/WMRefCounter.h"
#include "Graphics/Primitive/WMViewport.h"
#include "Graphics/WMTexture.h"
#include "Graphics/Primitive/WMColor.h"

namespace WildMini::Graphics
{
    class WMRenderCommandEncoder : public Object::WMRefCounter
    {
    public:
        virtual void SetViewport(const Primitive::WMViewport& viewport) = 0;
        virtual void SetScissorRect(const Primitive::WMRect& rect) = 0;
        virtual void SetRenderTarget(const WMTexture* renderTarget) = 0;
        virtual void ClearRenderTarget(const WMTexture* renderTarget, const Primitive::WMColor& color) = 0;
    };
}
