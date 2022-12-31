//
//  File:   WMComponent.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Common/WMObject.h"

namespace WildMini
{
    class WM_API WMComponent
    {
    public:
        virtual WildMini::Common::WMObject* GetOwner() = 0;
    };
}