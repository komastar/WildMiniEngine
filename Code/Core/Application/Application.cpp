#include "Application.h"
#include "Private/ApplicationContextFactory.h"

Core::Application::Application() : context(nullptr)
{
    context = ApplicationContextFactory::Create();
}

Core::Application::~Application()
{
    delete context;
    context = nullptr;
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
