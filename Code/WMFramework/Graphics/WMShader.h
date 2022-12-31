//
//  File:   WMShader.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMRefCounter.h"

namespace WildMini::Graphics
{
    class WM_API WMShader : public WildMini::WMRefCounter
    {
    public:
        enum class StageType
        {
            Vertex,
            Fragment
        };
    };
}
