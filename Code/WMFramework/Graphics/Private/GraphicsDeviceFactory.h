//
//  File:   GraphicsDeviceFactory.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

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
