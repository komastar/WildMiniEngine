//
//  ThreadContext.h
//  WMFramework
//
//  Created by Eugene Kim on 2022/08/08.
//

#ifndef Thread_h
#define Thread_h
#ifdef __APPLE__
#include "Common/WMThread.h"

namespace WildMini
{
    class ThreadContext : public WMThread
    {
    public:
        ThreadContext(const wchar_t* name);
        
    public:
        void Initialize(std::function<void ()> func) override;
        void Run() override;
        void Terminate() override;
    };
}
#endif /* __APPLE__ */
#endif /* Thread_h */
