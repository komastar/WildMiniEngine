//
//  File:   WMFileHandle.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"

namespace WildMini::IO::File
{
    struct WMFileHandle
    {
        std::fstream stream;
    };
}
