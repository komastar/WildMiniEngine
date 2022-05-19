#pragma once
class IApplicationContext;
namespace Core
{
    class IApplication
    {
    public:
        virtual void OnInitialize() = 0;
        virtual void OnTerminate() = 0;
        virtual int Run() = 0;

    private:
        IApplicationContext* context;
    };
}
