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

using namespace WildMini;

class UnitTestApplication : public WMApplication
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

        device = GraphicsDeviceFactory::Create();

        context = ApplicationContextFactory::Create();
    }
    
    void OnTerminate() override
    {
    }

private:
    WMSharedPtr<WMWindow> window;
    WMSharedPtr<WMGraphicsDevice> device;
};

_TEST_(Win32, App, Run)
{
    //UnitTestApplication testApp;
    //int result = testApp.Run();
}
