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

int ApplicationContext::ApplicationLoop()
{
    MSG msg;
    WMTimer timer;
    const double frameTime = 1.0 / 1.0;
    const std::chrono::duration<WMTick, std::nano> frame(16 * 1000000);
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            const auto start = std::chrono::high_resolution_clock::now();
            Tick();
            const auto end = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<WMTick, std::nano> elapsed = end - start;
            const std::chrono::duration<WMTick, std::nano> remain = frame - elapsed;
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
    WMLogDebug("Tick");
    for (auto& scene : scenes)
    {
        scene->Update(0.0f, 0);
        scene->Render();
    }
}
#endif // _WIN32
