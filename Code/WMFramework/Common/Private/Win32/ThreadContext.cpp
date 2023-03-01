#include "ThreadContext.h"
#include <Windows.h>

using namespace WildMini;

ThreadContext::ThreadContext(const wchar_t* name)
    : threadName(L"")
{
    if (name)
    {
        threadName = std::wstring(name);
    }
}

void ThreadContext::Initialize(std::function<void(void)> func)
{
    loop = func;
}

void ThreadContext::Run()
{
    thread = std::jthread([&](std::stop_token token)
        {
            if (!threadName.empty())
            {
                auto threadHandle = thread.native_handle();
                SetThreadDescription(threadHandle, threadName.c_str());
            }

            while (!token.stop_requested())
            {
                loop();
            }
        });
}

void ThreadContext::Terminate()
{
    thread.request_stop();
    thread.join();
}
