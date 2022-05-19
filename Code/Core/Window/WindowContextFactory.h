#pragma once
#include "WindowContext.h"

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
