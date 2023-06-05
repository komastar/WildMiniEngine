//
//  File:   ApplicationContext.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#ifdef _WIN32
#include "Application/Private/Win32/ApplicationContext.h"
#include "Common/WMTimer.h"
#include "Log/WMLog.h"

using namespace WildMini;

using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<WMTick, std::nano>;

int ApplicationContext::ApplicationLoop()
{
    MSG msg;
    WMTimer timer;
    const Duration frame(16 * 1000000);
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            const auto start = Clock::now();
            Tick();
            const auto end = Clock::now();
            const Duration elapsed = end - start;
            const Duration remain = frame - elapsed;
            std::this_thread::sleep_for(remain);
        }

        if (msg.message == WM_QUIT)
        {
            break;
        }
    }

    return static_cast<int>(msg.wParam);
}

void ApplicationContext::Tick()
{
    LogDebug("Tick");
    for (auto& [key, scene] : scenes)
    {
        scene->Update(0.0f, 0);
        scene->Render();
    }
}
#endif // _WIN32
