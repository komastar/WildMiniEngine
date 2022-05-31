#pragma once
#include "Graphics/Platform/DX/WMGraphicsDeviceContext.h"

namespace WildMini::Graphics
{
    class WMGraphicsDeviceFactory
    {
    public:
        static WMGraphicsDevice* Create(WildMini::Window::WMWindow* window = nullptr)
        {
            return WMGraphicsDeviceContext::Create(window);
        }
    };
}
