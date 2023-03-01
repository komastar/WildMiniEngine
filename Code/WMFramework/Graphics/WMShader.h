//
//  File:   WMShader.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMRefCounter.h"

namespace WildMini
{
    class WM_API WMShader : public WMRefCounter
    {
    public:
        enum class StageType
        {
            Vertex,
            Fragment
        };
    };
}
