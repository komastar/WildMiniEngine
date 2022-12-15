//
//  File:   WMSerializable.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"

using WMData = std::wstring;

namespace WildMini
{
    class WM_API WMSerailizable
    {
    public:
        virtual WMData Serialize() = 0;
        virtual void Deserialize(WMData data) = 0;
    };
}