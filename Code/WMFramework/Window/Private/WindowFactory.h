#pragma once
#include "Window/Private/Win32/WindowContext.h"

namespace WildMini::Window
{
    class WindowFactory
    {
    public:
        static WMWindow* Create()
        {
            return new WindowContext();
        }
    };
}
