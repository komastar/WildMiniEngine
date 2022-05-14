#pragma once

#include "GraphicsDeviceContext.h"

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
