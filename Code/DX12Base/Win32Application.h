#pragma once
#include "Application/Application.h"
#include <Windows.h>
#include "Window/Private/WindowFactory.h"
#include "Graphics/Private/DeviceFactory.h"

class Win32Application : public Core::Application
{
private:
    Core::IGraphicsDevice* device;
    Core::IWindow* window;

public:
    Win32Application();

public:
    virtual void OnInitialize() override;
    virtual void OnTerminate() override;
};

