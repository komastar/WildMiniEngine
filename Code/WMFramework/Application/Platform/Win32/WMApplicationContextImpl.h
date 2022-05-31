#pragma once
#ifdef _WIN32
#include <Windows.h>
#include "Application/WMApplicationContext.h"
#include "Graphics/WMGraphicsDevice.h"
#include "Object/WMObject.h"
#include "Window/WMWindow.h"

namespace WildMini::Application
{
    class WMApplicationContextImpl : public WMApplicationContext
    {
    public:
        WMApplicationContextImpl(WildMini::Window::WMWindow* _window, WildMini::Graphics::WMGraphicsDevice* _device);

    public:
        virtual int MessageLoop() override;

    private:
        WildMini::Object::WMObject<WildMini::Window::WMWindow> window;
        WildMini::Object::WMObject<WildMini::Graphics::WMGraphicsDevice> device;
        HWND platformHandle;
    };
}
#endif // _WIN32
