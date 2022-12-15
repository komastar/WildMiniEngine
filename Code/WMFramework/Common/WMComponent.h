//
//  File:   WMComponent.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"

namespace WildMini
{
    class WMBase;
    class WM_API WMComponent
    {
    public:
        virtual WMBase* GetOwner() = 0;
    };
}