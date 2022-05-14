#include "UnitTest.h"
#include "Application/Application.h"
#include "Window/Window.h"

class UnitTestApplication : public Core::IApplication
{
private:
    Core::IWindow* window;

public:
    UnitTestApplication() : window(nullptr)
    {
    }

    virtual void OnInitialize() override
    {
    }
    virtual void OnTerminate() override
    {
    }
    virtual int MessageLoop() override
    {
        return 0;
    }
};

_TEST_(Win32, App, Run)
{

}