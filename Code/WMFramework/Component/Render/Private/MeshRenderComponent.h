//
//  File:   MeshRenderComponent.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include "Component/Render/WMRenderComponent.h"

namespace WildMini
{
    class MeshRenderComponent : public WMRenderComponent
    {
    public:
        MeshRenderComponent(WMObject* owner);
    };
}