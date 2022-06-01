#include "WMGraphicsDevice.h"
#include "Graphics/Private/GraphicsDeviceFactory.h"

using namespace WildMini::Graphics;

WMGraphicsDevice* WMGraphicsDevice::CreateGraphicsDevice()
{
    return WildMini::Graphics::Private::GraphicsDeviceFactory::Create();
}
