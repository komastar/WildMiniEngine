#pragma once

#include "Graphics/Platform/Win32/GraphicsDeviceContext.h"

namespace Core
{
    class DeviceContextFactory
    {
    public:
        static IGraphicsDevice* Create()
        {
            return new GraphicsDeviceContext();
        }
    };
}
