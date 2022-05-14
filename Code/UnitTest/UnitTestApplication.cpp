#include "UnitTest.h"
#include "Application/Application.h"
#include "Window/IWindow.h"
#include "Window/WindowContextFactory.h"

class UnitTestApplication : public Core::Application
{
private:
    Core::IWindow* window;

public:
    UnitTestApplication() : window(nullptr)
    {
    }

    virtual void OnInitialize() override
    {
        window = Core::WindowContextFactory::Create();
        window->Create();
        window->Show();
        window->Focus();
    }
    
    virtual void OnTerminate() override
    {
        delete window;
        window = nullptr;
    }
};

_TEST_(Win32, App, Run)
{
    UnitTestApplication testApp;
    testApp.Run();
}