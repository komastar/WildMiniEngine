#include "Application/Application.h"

Core::Application::Application()
    : context(nullptr)
    , device(nullptr)
    , window(nullptr)
{
}

void Core::Application::OnInitialize()
{
}

void Core::Application::OnTerminate()
{
}

int Core::Application::Run()
{
    OnInitialize();
    int msg = context->MessageLoop();
    OnTerminate();
    return msg;
}
