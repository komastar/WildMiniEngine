#pragma once
#include "Object/WMRefCounter.h"

namespace WildMini::Graphics
{
    class WMCommandBuffer : public WildMini::Object::WMRefCounter
    {
    public:
        virtual void CreateRenderCommandEncoder() = 0;
        virtual void Commit() = 0;
    };
}
