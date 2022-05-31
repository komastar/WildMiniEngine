#include "UnitTest.h"
#include "Application/WMApplication.h"
#include "Window/Platform/WMWindowtFactory.h"
#include "Application/Platform/WMApplicationContextFactory.h"
#include "Graphics/Platform/WMGraphicsDeviceFactory.h"

using namespace WildMini::Window;

class UnitTestApplication : public WildMini::Application::WMApplication
{
public:
    UnitTestApplication() {}
    virtual ~UnitTestApplication() {}

    void OnInitialize() override
    {
        window = WMWindowtFactory::Create();
        window->Create();
        window->Show();
        window->Focus();

        device = WildMini::Graphics::WMGraphicsDeviceFactory::Create(window);

        context = WildMini::Application::WMApplicationContextFactory::Create(window, device);
    }
    
    void OnTerminate() override
    {
    }
};

_TEST_(Win32, App, Run)
{
    UnitTestApplication testApp;
    int result = testApp.Run();
}
