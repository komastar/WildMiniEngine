#include "WMThread.h"
#include "Common/Private/Win32/ThreadContext.h"
#include "Common/Private/Cocoa/ThreadContext.h"

using namespace WildMini;

WMThread* WMThread::Create(const wchar_t* name)
{
    return new ThreadContext(name);
}
