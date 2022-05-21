#include "UnitTest.h"
#include "Application/Application.h"
#include "Window/Platform/WindowContextFactory.h"
#include "Application/Platform/ApplicationContextFactory.h"
#include "Graphics/Platform/DeviceContextFactory.h"

class UnitTestApplication : public Core::Application
{
public:
    UnitTestApplication() {}
    virtual ~UnitTestApplication() {}

    virtual void OnInitialize() override
    {
        window = Core::WindowContextFactory::Create();
        window->Create();
        window->Show();
        window->Focus();

        device = Core::DeviceContextFactory::Create(window);

        context = Core::ApplicationContextFactory::Create(window, device);
    }
    
    virtual void OnTerminate() override
    {
    }
};

_TEST_(Win32, App, Run)
{
    UnitTestApplication testApp;
    int result = testApp.Run();
}
