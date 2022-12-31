//
//  File:   WMRefCounter.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"

namespace WildMini
{
    class WM_API WMRefCounter
    {
    public:
        WMRefCounter()
            : refCount(0)
        {
        }

        virtual ~WMRefCounter() noexcept
        {
            assert(0 == refCount);
        }

        uint32_t AddRef()
        {
            return ++refCount;
        }

        uint32_t Release()
        {
            return --refCount;
        }

        uint32_t RefCount() const
        {
            return refCount;
        }

    private:
        struct WM_API std::atomic<uint32_t> refCount;
    };
}
