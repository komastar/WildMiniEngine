//
//  File:   WMComponentBase.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "Component/WMComponent.h"

namespace WildMini
{
    class WMComponentBase : public WMComponent
    {
    public:
        WMComponentBase(WMObject*);

    protected:
        WMObject* owner;

    public:
        virtual WMObject* GetOwner() override;
    };
}
