#pragma once
#include "WMFramework.h"

#include <cstdint>
#include <atomic>

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
