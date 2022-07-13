//
//  File:   ApplicationContext.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#ifdef _WIN32
#include "Application/Private/Win32/ApplicationContext.h"

using namespace WildMini::Application::Private;

int ApplicationContext::MessageLoop()
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
