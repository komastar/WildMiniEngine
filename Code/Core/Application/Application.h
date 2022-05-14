#pragma once
#include "IApplication.h"
#include "IApplicationContext.h"

namespace Core
{
    class Application : public IApplication
    {
    public:
        Application();
        virtual ~Application();

    public:
        virtual void OnInitialize() override;
        virtual void OnTerminate() override;
        virtual int Run() override;

    private:
        IApplicationContext* context;
    };
}
#pragma once
