#pragma once
#include "Common/Object.h"
#include "IApplication.h"
#include "IApplicationContext.h"
#include "Graphics/IGraphicsDevice.h"
#include "Window/IWindow.h"

namespace Core
{
    class Application : public IApplication
    {
    public:
        Application();

    public:
        virtual void OnInitialize() override;
        virtual void OnTerminate() override;
        virtual int Run() override;

    protected:
        Object<IApplicationContext> context;
        Object<IGraphicsDevice> device;
        Object<IWindow> window;
    };
}
#pragma once
