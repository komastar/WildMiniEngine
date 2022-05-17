#include "UnitTest.h"
#include "Application/Application.h"
#include "Window/WindowContextFactory.h"
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

        device = Core::DeviceContextFactory::Create();
        device->Create(window);

        context = Core::ApplicationContextFactory::Create(window, device);
    }
    
    virtual void OnTerminate() override
    {
        delete context;
        context = nullptr;

        delete device;
        device = nullptr;

        delete window;
        window = nullptr;
    }
};

TEST(App, Run)
{
    UnitTestApplication testApp;
    int result = testApp.Run();
}

//_TEST_(Win32, App, Run)
//{
//}