#pragma once
#include "Object/WMRefCounter.h"

namespace WildMini::Window
{
    class WMWindow : public WildMini::Object::WMRefCounter
    {
    public:
        virtual void Create() = 0;
        virtual void Show() = 0;
        virtual void Hide() = 0;
        virtual void Update() = 0;
        virtual void Focus() = 0;

        virtual void* PlatformHandle() = 0;

        virtual uint32_t Width() = 0;
        virtual uint32_t Height() = 0;
    };
}
