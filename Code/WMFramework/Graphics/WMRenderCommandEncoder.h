#pragma once
#include "Object/WMRefCounter.h"

namespace WildMini::Graphics
{
    class WMRenderCommandEncoder : WildMini::Object::WMRefCounter
    {
    public:
        virtual void SetViewport() = 0;
        virtual void SetScissorRect() = 0;
        virtual void SetRenderTarget() = 0;
        virtual void ClearRenderTarget() = 0;
    };
}
