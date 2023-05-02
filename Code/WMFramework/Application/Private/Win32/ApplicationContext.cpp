//
//  File:   ApplicationContext.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#ifdef _WIN32
#include "Application/Private/Win32/ApplicationContext.h"

using namespace WildMini;

int ApplicationContext::MessageLoop()
{
    bool isRunning = true;
    MSG msg;
    while (isRunning)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (WM_QUIT == msg.message)
        {
            isRunning = false;
            break;
        }
    }

    return static_cast<int>(msg.wParam);
}
#endif // _WIN32
