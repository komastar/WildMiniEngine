#pragma once
#include <cstdint>
#include <atomic>

namespace WildMini::Object
{
    class WMRefCounter
    {
    public:
        WMRefCounter();
        virtual ~WMRefCounter() noexcept;

        uint32_t AddRef();
        uint32_t Release();
        uint32_t RefCount() const;

    private:
        struct std::atomic<uint32_t> refCount;
    };
}
