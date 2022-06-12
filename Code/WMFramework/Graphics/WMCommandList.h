#pragma once
#include "Object/WMRefCounter.h"
#include "Graphics/Primitive/WMViewport.h"
#include "Graphics/Primitive/WMRect.h"
#include "Graphics/Primitive/WMColor.h"
#include "Graphics/WMTexture.h"

namespace WildMini::Graphics
{
    class WMCommandList : public WildMini::Object::WMRefCounter
    {
    public:
        virtual void SetViewport(const Primitive::WMViewport& viewport) = 0;
        virtual void SetScissorRect(const Primitive::WMRect& rect) = 0;
        virtual void SetRenderTarget(const Graphics::WMTexture* renderTarget) = 0;
        virtual void ClearRenderTarget(const Graphics::WMTexture* renderTarget, const Primitive::WMColor& color) = 0;
        virtual void Close() = 0;
        virtual void Reset() = 0;
    };
}
