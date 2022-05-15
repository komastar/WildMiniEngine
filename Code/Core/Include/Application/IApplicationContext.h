#pragma once
namespace Core
{
    class IWindow;
    class IGraphicsDevice;
    class IApplicationContext
    {
    public:
        virtual int MessageLoop() = 0;

    protected:
        IGraphicsDevice* device;
        IWindow* window;
    };
}