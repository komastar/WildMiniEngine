//
//  File:   WMMaterial.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include "WMRefCounter.h"
#include "Graphics/WMTexture.h"

namespace WildMini
{
    class WMMaterial : public WMRefCounter
    {
    protected:
        WMSharedPtr<WMTexture> texture;
    };
}
