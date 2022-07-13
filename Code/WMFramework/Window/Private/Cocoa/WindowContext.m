//
//  WindowContext.m
//  WMFramework
//
//  Created by Eugene Kim on 2022/06/06.
//

#ifdef __APPLE__
#include "WindowContext.h"

@interface WindowDelegate : NSObject<NSWindowDelegate>
@end

@implementation WindowDelegate

- (void)windowWillClose:(NSNotification *)notification
{
    [NSApp stop:nil];
}
@end

WildMini::Window::WindowContext::WindowContext()
    : window(nil)
    , view(nil)
{
}
#endif // __APPLE__
