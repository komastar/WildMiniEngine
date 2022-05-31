#pragma once
#include "Object/WMRefCounter.h"

namespace WildMini::Graphics
{
    class WMCommandList : public WildMini::Object::WMRefCounter
    {
    public:
        virtual void Close() = 0;
        virtual void Reset() = 0;
    };
}
