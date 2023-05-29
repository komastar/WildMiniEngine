//
//  File:   Timer.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#include "TimerContext.h"
#include <windows.h>

using namespace WildMini;

using Clock = std::chrono::high_resolution_clock;

TimerContext::TimerContext()
{
    QueryPerformanceFrequency((LARGE_INTEGER*)&period);
    scale = 1.0 / static_cast<double>(period);

    Reset();
}

TimerContext::~TimerContext()
{
}

double TimerContext::Elapsed()
{
    double elapsed = (Tick() - prev) * scale;
    Reset();
    return elapsed;
}

void TimerContext::Reset()
{
    QueryPerformanceCounter((LARGE_INTEGER*)&prev);
}

WMTick TimerContext::Tick() const
{
    WMTick tick = 0;
    QueryPerformanceCounter((LARGE_INTEGER*)&tick);
    return tick;
}
