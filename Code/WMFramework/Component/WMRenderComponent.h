//
//  File:   WMRenderComponent.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include "Component/WMComponentBase.h"
#include "Graphics/WMTexture.h"

namespace WildMini
{
    class WMRenderComponent : public WMComponentBase
    {
    public:
        virtual void Render(WMTexture* renderTarget) = 0;
    };
}
