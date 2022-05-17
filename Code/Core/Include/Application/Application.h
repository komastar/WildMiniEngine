#pragma once
#include "IApplication.h"
#include "IApplicationContext.h"
#include "Graphics/IGraphicsDevice.h"

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
        IApplicationContext* context;
        IGraphicsDevice* device;
        IWindow* window;
    };
}
#pragma once
