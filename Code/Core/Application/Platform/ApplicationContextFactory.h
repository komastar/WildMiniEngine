#pragma once
#include "Application/IApplication.h"
#include "Win32/ApplicationContext.h"

namespace Core
{
    class IWindow;
    class IGraphicsDevice;
    class ApplicationContextFactory
    {
    public:
        static IApplicationContext* Create(IWindow* window = nullptr, IGraphicsDevice* device = nullptr)
        {
            return new ApplicationContext(window, device);
        }
    };
}
