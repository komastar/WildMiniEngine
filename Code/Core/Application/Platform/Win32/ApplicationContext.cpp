#ifdef _WIN32
#include "Application/Platform/Win32/ApplicationContext.h"

int Core::ApplicationContext::MessageLoop()
{
    MSG msg;
    BOOL isFrame = FALSE;
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
        else
        {
            device->Update();
            device->Render();
        }
    }

    return static_cast<int>(msg.wParam);
}

Core::ApplicationContext::ApplicationContext(IWindow* _window, IGraphicsDevice* _device)
    : window(_window)
    , device(_device)
    , platformHandle(nullptr)
{
    platformHandle = reinterpret_cast<HWND>(window->PlatformHandle());
}
#endif // _WIN32
