//
//  File:   WMRefCounter.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"

namespace WildMini::Object
{
    class WM_API WMRefCounter
    {
    public:
        WMRefCounter();
        virtual ~WMRefCounter() noexcept;

        uint32_t AddRef();
        uint32_t Release();
        uint32_t RefCount() const;

    private:
        struct WM_API std::atomic<uint32_t> refCount;
    };
}
