#pragma once
#include "Window/Platform/Win32/WindowContext.h"

namespace Core
{
    class WindowContextFactory
    {
    public:
        static IWindow* Create()
        {
            return new WindowContext();
        }
    };
}
