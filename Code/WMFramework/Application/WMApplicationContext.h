#pragma once
#include "Object/WMObject.h"
#include "Window/WMWindow.h"
#include "Graphics/WMGraphicsDevice.h"

namespace WildMini::Application
{
    class WMApplicationContext : public WildMini::Object::WMRefCounter
    {
    public:
        virtual int MessageLoop() = 0;

    protected:
        WildMini::Object::WMObject<WildMini::Graphics::WMGraphicsDevice> device;
        WildMini::Object::WMObject<WildMini::Window::WMWindow> window;
    };
}
