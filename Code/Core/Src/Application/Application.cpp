#include "Application/Application.h"
#include "Application/ApplicationContextFactory.h"
#include "Window/WindowContextFactory.h"
#include "Graphics/DeviceContextFactory.h"

Core::Application::Application()
    : context(nullptr)
    , device(nullptr)
    , window(nullptr)
{
    context = ApplicationContextFactory::Create();
}

void Core::Application::OnInitialize()
{
    window = Core::WindowContextFactory::Create();
    window->Create();
    window->Show();
    window->Focus();

    device = Core::DeviceContextFactory::Create();
    device->Create(window);
}

void Core::Application::OnTerminate()
{
    delete context;
    context = nullptr;
}

int Core::Application::Run()
{
    OnInitialize();
    int msg = context->MessageLoop();
    OnTerminate();
    return msg;
}
