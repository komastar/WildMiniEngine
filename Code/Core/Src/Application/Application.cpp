#include "Application/Application.h"
#include "Application/Platform/ApplicationContextFactory.h"
#include "Window/WindowContextFactory.h"
#include "Graphics/Platform/DeviceContextFactory.h"

Core::Application::Application()
    : context(nullptr)
    , device(nullptr)
    , window(nullptr)
{
}

void Core::Application::OnInitialize()
{
    window = Core::WindowContextFactory::Create();
    window->Create();
    window->Show();
    window->Focus();

    device = Core::DeviceContextFactory::Create();
    device->Create(window);

    context = ApplicationContextFactory::Create(window, device);
}

void Core::Application::OnTerminate()
{
    delete context;
    context = nullptr;

    delete device;
    device = nullptr;

    delete window;
    window = nullptr;
}

int Core::Application::Run()
{
    OnInitialize();
    int msg = context->MessageLoop();
    OnTerminate();
    return msg;
}
