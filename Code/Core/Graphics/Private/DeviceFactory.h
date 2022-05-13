#pragma once

#include "Win32/GraphicsDeviceContext.h"

namespace Core
{
    class DeviceFactory
    {
    public:
        static IGraphicsDevice* Create()
        {
            return new GraphicsDeviceContext();
        }
    };
}
