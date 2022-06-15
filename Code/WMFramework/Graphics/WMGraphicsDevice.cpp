//
//  File:   WMGraphicsDevice.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMGraphicsDevice.h"
#include "Graphics/Private/GraphicsDeviceFactory.h"

using namespace WildMini::Graphics;

WMGraphicsDevice* WMGraphicsDevice::CreateGraphicsDevice()
{
    return WildMini::Graphics::Private::GraphicsDeviceFactory::Create();
}
