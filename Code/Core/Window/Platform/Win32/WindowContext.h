#pragma once
#include <Windows.h>
#include "Window/IWindow.h"

namespace Core
{
    class WindowContext : public IWindow
    {
    public:
        virtual void Create() override;
        virtual void Show() override;
        virtual void Hide() override;
        virtual void* PlatformHandle() override;
        virtual int Width() override;
        virtual int Height() override;
        virtual void Update() override;
        virtual void Focus() override;

    protected:
        HINSTANCE instance;
        HWND hwnd;

    private:
        const int width = 1024;
        const int height = 768;
    };
}
