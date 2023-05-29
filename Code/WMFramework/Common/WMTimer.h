//
//  File:   WMTimer.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Common/WMTimerContext.h"

namespace WildMini
{
    class WM_API WMTimer
    {
    public:
        WMTimer();
        ~WMTimer();

    public:
        double Elapsed() const;
        void Reset();
        WMTick Tick() const;

    private:
        WMTimerContext* impl;
    };
}
