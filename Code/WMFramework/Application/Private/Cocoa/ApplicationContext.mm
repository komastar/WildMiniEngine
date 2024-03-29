//
//  ApplicationContext.m
//  WMFramework
//
//  Created by Eugene Kim on 2022/06/06.
//

#ifdef __APPLE__
#include "ApplicationContext.h"
#include <TargetConditionals.h>
#import <Cocoa/Cocoa.h>

using namespace WildMini;

int ApplicationContext::MessageLoop()
{
    NSApplication* app = [NSApplication sharedApplication];
    [app run];
    return 0;
}

#endif /* __APPLE__ */
