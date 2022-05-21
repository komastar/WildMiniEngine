#pragma once
#include "Graphics/Platform/DX/GraphicsDeviceContext.h"

namespace Core
{
    class DeviceContextFactory
    {
    public:
        static IGraphicsDevice* Create(IWindow* window = nullptr)
        {
            return GraphicsDeviceContext::Create(window);
        }
    };
}
