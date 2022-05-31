#pragma once
#include "Object/WMObject.h"
#include "WMApplication.h"
#include "WMApplicationContext.h"
#include "Graphics/WMGraphicsDevice.h"
#include "Window/WMWindow.h"

namespace WildMini::Application
{
    class WMApplication : public WildMini::Object::WMRefCounter
    {
    public:
        WMApplication();

    public:
        virtual void OnInitialize() = 0;
        virtual void OnTerminate() = 0;
        int Run();

    protected:
        WildMini::Object::WMObject<WMApplicationContext> context;
        WildMini::Object::WMObject<WildMini::Graphics::WMGraphicsDevice> device;
        WildMini::Object::WMObject<WildMini::Window::WMWindow> window;
    };
}
#pragma once
