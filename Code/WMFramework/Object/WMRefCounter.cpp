#include "WMRefCounter.h"
#include <cassert>

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
