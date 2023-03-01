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
    MSG msg;
    while (true)
    {
        if (GetMessageW(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Update();
            Render();
        }

        if (WM_QUIT == msg.message)
        {
            break;
        }
    }

    return static_cast<int>(msg.wParam);
}
void WildMini::ApplicationContext::Update()
{
}
void WildMini::ApplicationContext::Render()
{
}
#endif // _WIN32
