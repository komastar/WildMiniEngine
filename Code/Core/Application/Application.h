#pragma once
namespace Core
{
    class IApplication
    {
    public:
        virtual void OnInitialize() = 0;
        virtual void OnTerminate() = 0;
        virtual int Run();

        virtual int MessageLoop() = 0;
    };
}
