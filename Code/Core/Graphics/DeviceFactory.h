#pragma once
#include "D3D12Device.h"

class GraphicsDevice;

class DeviceFactory
{
public:
    static GraphicsDevice* Create()
    {
        return new D3D12Device();
    }
};