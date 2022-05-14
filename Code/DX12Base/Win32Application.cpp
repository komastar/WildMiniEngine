#include "Win32Application.h"

Win32Application::Win32Application()
    : window(nullptr)
    , device(nullptr)
{
}

void Win32Application::OnInitialize()
{
    window = Core::WindowFactory::Create();
    window->Create();
    window->Show();
    window->Focus();

    device = Core::DeviceFactory::Create();
    device->Create(window);
}

void Win32Application::OnTerminate()
{
    delete window;
    window = nullptr;

    delete device;
    device = nullptr;
}
