#ifdef _WIN32
#include "Application/ApplicationContext.h"
#include "Graphics/IGraphicsDevice.h"
#include <Windows.h>

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
#endif // _WIN32