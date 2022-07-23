#include "WMThread.h"
#include "Common/Private/Win32/ThreadContext.h"

using namespace WildMini::Common;

WMThread* WMThread::Create(const wchar_t* name)
{
    return new WildMini::Common::Thread::ThreadContext(name);
}
