//
//  File:   WMTimer.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#include "WMTimer.h"
#ifdef _WIN32
#include "Common/Private/Win32/TimerContext.h"
#endif // _WIN32

using namespace WildMini;

WMTimer::WMTimer()
{
    impl = new TimerContext();
}

WMTimer::~WMTimer()
{
    WMASSERT(impl);
    delete impl;
    impl = nullptr;
}

double WMTimer::Elapsed() const
{
    WMASSERT(impl);
    return impl->Elapsed();
}

void WMTimer::Reset()
{
    WMASSERT(impl);
    impl->Reset();
}

WMTick WMTimer::Tick() const
{
    WMASSERT(impl);
    return impl->Tick();
}
