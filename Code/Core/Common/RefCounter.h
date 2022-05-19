#pragma once
#include <cstdint>
#include <atomic>

namespace Core
{
    class RefCounter
    {
    public:
        RefCounter();
        virtual ~RefCounter() noexcept;

        uint32_t AddRef();
        uint32_t Release();
        uint32_t RefCount() const;

    private:
        struct std::atomic<uint32_t> refCount;
    };
}