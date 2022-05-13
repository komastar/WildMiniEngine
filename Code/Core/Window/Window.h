#pragma once
namespace Core
{
    class IWindow
    {
    public:
        virtual void Create() = 0;
        virtual void Show() = 0;
        virtual void Hide() = 0;
        virtual void Update() = 0;
        virtual void Focus() = 0;

        virtual void* PlatformHandle() = 0;

        virtual int Width() = 0;
        virtual int Height() = 0;
    };
}
