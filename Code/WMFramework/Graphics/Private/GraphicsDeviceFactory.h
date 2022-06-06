#pragma once
#include "Graphics/Private/DX12/GraphicsDeviceContext.h"

namespace WildMini::Graphics::Private
{
    class GraphicsDeviceFactory
    {
    public:
        static WMGraphicsDevice* Create()
        {
#ifdef __APPLE__
            return nullptr;
#else
            return new GraphicsDeviceContext();
#endif // __APPLE__
        }
    };
}
