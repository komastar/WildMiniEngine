//
//  File:   WMTimerContext.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"

namespace WildMini
{
    class WMTimerContext
    {
    public:
        virtual double Elapsed() = 0;
        virtual void Reset() = 0;
        virtual WMTick Tick() const = 0;
    };
}