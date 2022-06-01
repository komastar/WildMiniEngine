#pragma once
#include "Graphics/Private/DX12/GraphicsDeviceContext.h"

namespace WildMini::Graphics::Private
{
    class GraphicsDeviceFactory
    {
    public:
        static WMGraphicsDevice* Create()
        {
            return new GraphicsDeviceContext();
        }
    };
}
