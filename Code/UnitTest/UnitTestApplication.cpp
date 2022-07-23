//
//  File:   UnitTestApplication.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "UnitTest.h"
#include "Application/WMApplication.h"
#include "Window/Private/WindowFactory.h"
#include "Application/Private/ApplicationContextFactory.h"
#include "Graphics/Private/GraphicsDeviceFactory.h"

using namespace WildMini::Window;

class UnitTestApplication : public WildMini::Application::WMApplication
{
public:
    UnitTestApplication() {}
    virtual ~UnitTestApplication() {}

    void OnInitialize() override
    {
        window = WindowFactory::Create(800, 600);
        window->Create();
        window->Show();
        window->Focus();

        device = WildMini::Graphics::Private::GraphicsDeviceFactory::Create();

        context = WildMini::Application::Private::ApplicationContextFactory::Create();
    }
    
    void OnTerminate() override
    {
    }

private:
    WildMini::Object::WMObject<WildMini::Window::WMWindow> window;
    WildMini::Object::WMObject<WildMini::Graphics::WMGraphicsDevice> device;
};

_TEST_(Win32, App, Run)
{
    //UnitTestApplication testApp;
    //int result = testApp.Run();
}
