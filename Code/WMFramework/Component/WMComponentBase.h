//
//  File:   WMComponentBase.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "Component/WMComponent.h"

namespace WildMini::Component
{
    class WMComponentBase : public WildMini::WMComponent
    {
    public:
        WMComponentBase(WildMini::Common::WMObject*);

    protected:
        WildMini::Common::WMObject* owner;

    public:
        virtual WildMini::Common::WMObject* GetOwner() override;
    };
}

