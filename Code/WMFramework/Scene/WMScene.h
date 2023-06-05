//
//  File:   WMScene.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMRefCounter.h"

namespace WildMini
{
    class WM_API WMScene : public WMRefCounter
    {
    public:
        virtual void Update(const float dt, const uint64_t tick) = 0;
        virtual void Render() = 0;
    };
}