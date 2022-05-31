#ifdef _WIN32
#include "Application/Platform/Win32/WMApplicationContextImpl.h"

using namespace WildMini::Application;

WMApplicationContextImpl::WMApplicationContextImpl(WildMini::Window::WMWindow* _window, WildMini::Graphics::WMGraphicsDevice* _device)
    : window(_window)
    , device(_device)
    , platformHandle(nullptr)
{
    platformHandle = reinterpret_cast<HWND>(window->PlatformHandle());
}

int WMApplicationContextImpl::MessageLoop()
{
    MSG msg;
    while (true)
    {
        if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (WM_QUIT == msg.message)
        {
            break;
        }
    }

    return static_cast<int>(msg.wParam);
}
#endif // _WIN32
