#pragma once
#include "Object/WMRefCounter.h"
#include "Graphics/WMRenderCommandEncoder.h"

namespace WildMini::Graphics
{
    class WMCommandBuffer : public Object::WMRefCounter
    {
    public:
        virtual Object::WMObject<WMRenderCommandEncoder> CreateRenderCommandEncoder() = 0;
        virtual void Commit() = 0;
    };
}
