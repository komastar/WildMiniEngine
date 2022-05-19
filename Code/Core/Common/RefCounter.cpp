#include "Common/RefCounter.h"
#include <cassert>

Core::RefCounter::RefCounter()
    : refCount(0)
{
}

Core::RefCounter::~RefCounter() noexcept
{
    assert(0 == refCount);
}

uint32_t Core::RefCounter::AddRef()
{
    return ++refCount;
}

uint32_t Core::RefCounter::Release()
{
    return --refCount;
}

uint32_t Core::RefCounter::RefCount() const
{
    return refCount;
}
