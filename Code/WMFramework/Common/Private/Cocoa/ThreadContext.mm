//
//  ThreadContext.mm
//  WMFramework
//
//  Created by Eugene Kim on 2022/08/08.
//
#include "ThreadContext.h"
#import <Foundation/Foundation.h>

using namespace WildMini;

ThreadContext::ThreadContext(const wchar_t* name)
: isRunning(false)
{
    threadName = name;
}

void ThreadContext::Initialize(std::function<void ()> func)
{
    loop = func;
}

void ThreadContext::Run()
{
    isRunning = true;
    thread = std::thread([&]() {
        while (isRunning) {
            loop();
        }
    });
}

void ThreadContext::Terminate()
{
    isRunning = false;
    thread.join();
}
