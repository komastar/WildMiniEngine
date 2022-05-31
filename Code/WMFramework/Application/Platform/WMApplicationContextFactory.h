#pragma once
#include "Application/WMApplication.h"
#include "Win32/WMApplicationContextImpl.h"
#include "Window/WMWindow.h"
#include "Graphics/WMGraphicsDevice.h"

namespace WildMini::Application
{
    class WMApplicationContextFactory
    {
    public:
        static WMApplicationContext* Create(WildMini::Window::WMWindow* window = nullptr, WildMini::Graphics::WMGraphicsDevice* device = nullptr)
        {
            return new WMApplicationContextImpl(window, device);
        }
    };
}
