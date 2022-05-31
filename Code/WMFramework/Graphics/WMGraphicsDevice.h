#pragma once
#include "Object/WMRefCounter.h"

namespace WildMini::Graphics
{
    class WMGraphicsDevice : public WildMini::Object::WMRefCounter
    {
    public:
        virtual void Create() = 0;
    };
}
