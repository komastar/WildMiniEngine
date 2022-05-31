#pragma once
#include "Window/Platform/Win32/WMWindowContext.h"

namespace WildMini::Window
{
    class WMWindowtFactory
    {
    public:
        static WMWindow* Create()
        {
            return new WMWindowContext();
        }
    };
}
