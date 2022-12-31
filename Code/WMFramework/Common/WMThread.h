#pragma once
#include "WMFramework.h"
#include "WMRefCounter.h"

namespace WildMini::Common
{
    class WMThread : public WildMini::WMRefCounter
    {
    public:
        static WMThread* Create(const wchar_t* name);

    public:
        WMThread(const wchar_t* name);

    protected:
        WMThread() = default;

    public:
        virtual void Initialize(std::function<void(void)> func) = 0;
        virtual void Run() = 0;
        virtual void Terminate() = 0;
    };
}