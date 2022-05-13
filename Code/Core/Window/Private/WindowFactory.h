#pragma once
#include "Win32/WindowContext.h"

namespace Core
{
    class WindowFactory
    {
    public:
        static IWindow* Create()
        {
            return new WindowContext();
        }
    };
}
