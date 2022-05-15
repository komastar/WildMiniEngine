#pragma once
#ifdef _WIN32
#include <Windows.h>
#include "Application/IApplicationContext.h"
#include "Graphics/IGraphicsDevice.h"
#include "Window/IWindow.h"

namespace Core
{
    class ApplicationContext : public IApplicationContext
    {
    public:
        ApplicationContext();
        ApplicationContext(IWindow* _window, IGraphicsDevice* _device);

    public:
        virtual int MessageLoop() override;

    private:
        IWindow* window;
        IGraphicsDevice* device;
        HWND platformHandle;
    };
}
#endif // _WIN32
