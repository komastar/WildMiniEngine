#pragma once
#ifdef _WIN32
#include "Common/WMThread.h"

namespace WildMini
{
    class ThreadContext : public WMThread
    {
    public:
        ThreadContext(const wchar_t* name);

    public:
        virtual void Initialize(std::function<void(void)> func) override;
        virtual void Run() override;
        virtual void Terminate() override;

    private:
        std::function<void(void)> loop;
        std::jthread thread;
        std::wstring threadName;
    };
}
#endif
