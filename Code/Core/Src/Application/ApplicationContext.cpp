#ifdef _WIN32
#include "Application/ApplicationContext.h"
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
    }

    return static_cast<int>(msg.wParam);
}
#endif // _WIN32