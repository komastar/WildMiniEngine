#include "stdafx.h"
#include "DX12Base.h"
#include "WindowsApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
    WindowsApplication app(hInstance);
    app.OnInitialize();

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

    app.OnTerminate();

    return (int) msg.wParam;
}