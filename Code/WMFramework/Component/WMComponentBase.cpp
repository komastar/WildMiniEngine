//
//  File:   WMComponentBase.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#include "WMComponentBase.h"
#include "Common/WMObject.h"

using namespace WildMini;

WMComponentBase::WMComponentBase(WMObject* _owner)
    : owner(_owner)
{
}

WMObject* WMComponentBase::GetOwner()
{
    return owner;
}
