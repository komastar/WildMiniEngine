#pragma once
namespace Core
{
    class IWindow;
    class IGraphicsDevice
    {
    public:
        virtual void Create(IWindow* window) = 0;
    };
}
