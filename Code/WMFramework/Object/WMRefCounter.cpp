//
//  File:   WMRefCounter.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMRefCounter.h"

using namespace WildMini::Object;

WMRefCounter::WMRefCounter()
    : refCount(0)
{
}

WMRefCounter::~WMRefCounter() noexcept
{
    assert(0 == refCount);
}

uint32_t WMRefCounter::AddRef()
{
    return ++refCount;
}

uint32_t WMRefCounter::Release()
{
    return --refCount;
}

uint32_t WMRefCounter::RefCount() const
{
    return refCount;
}
