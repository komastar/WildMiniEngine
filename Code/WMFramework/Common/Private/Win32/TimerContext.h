//
//  File:   Timer.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include "Common/WMTimerContext.h"

namespace WildMini
{
    class TimerContext : public WMTimerContext
    {
    public:
        TimerContext();
        ~TimerContext();

    public:
        virtual double Elapsed() override;
        virtual void Reset() override;
        virtual WMTick Tick() const override;

    private:
        WMTick prev;
        WMTick period;
        double scale;
    };
}
