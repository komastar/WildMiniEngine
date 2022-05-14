#pragma once
namespace Core
{
    class IGraphicsDevice;
    class IApplicationContext
    {
    public:
        virtual int MessageLoop() = 0;

    public:
        IGraphicsDevice* device;
    };
}