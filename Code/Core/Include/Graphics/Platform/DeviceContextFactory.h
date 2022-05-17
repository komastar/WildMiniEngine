#pragma once

#include "Graphics/Platform/DX/GraphicsDeviceContext.h"

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
