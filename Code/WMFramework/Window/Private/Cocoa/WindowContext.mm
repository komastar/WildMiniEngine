//
//  WindowContext.m
//  WMFramework
//
//  Created by Eugene Kim on 2022/06/06.
//

#ifdef __APPLE__
#include "WindowContext.h"

using namespace WildMini;

WindowContext::WindowContext(uint32_t _width, uint32_t _height)
    : WMWindow(_width, _height)
    , window(nil)
    , view(nil)
{
}

void* WindowContext::PlatformHandle() const
{
    return nil;
}

float WindowContext::GetWidth() const
{
    return width;
}

float WindowContext::GetHeight() const
{
    return height;
}

void WindowContext::Create()
{
    //NSRect rect = NSMakeRect(0, 0, width, height);
    //window = [[NSWindow alloc] initWithContentRect:rect styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable backing:NSBackingStoreBuffered defer:NO];
    //[window setTitle: @"Editor"];
    //[window setReleasedWhenClosed:YES];
    
    //view = [[NSView alloc] initWithFrame:[window backingAlignedRect:rect options:NSAlignAllEdgesOutward]];
    //[window setContentView:view];
    //[window setDelegate:[WindowDelegate alloc]];
}

void WindowContext::Show()
{
}

void WindowContext::Hide()
{
}

void WindowContext::Update()
{
}

void WindowContext::Focus()
{
}

void WindowContext::SetTitle(const wchar_t* title)
{
    NSString* titleStr = [[[NSString alloc] initWithBytes:title length:wcslen(title)*sizeof(*title) encoding:NSUTF32LittleEndianStringEncoding] autorelease];
    [window setTitle: titleStr];
}

void WindowContext::SetWidth(uint32_t _width)
{
    width = _width;
}

void WindowContext::SetHeight(uint32_t _height)
{
    height = _height;
}

void WindowContext::SetSize(uint32_t _width, uint32_t _height)
{
    width = _width;
    height = _height;
}

float WindowContext::GetAspect() const
{
    return static_cast<float>(width) / static_cast<float>(height);
}

void WindowContext::OnResize()
{
}

void WindowContext::AddResizeCallback(std::function<void (uint32_t, uint32_t)> callback)
{
}

WMWindow* WindowContext::AddMouseEventHandler(std::function<void (WMMouseEvent)> handler)
{
    return nullptr;
}

WMWindow* WindowContext::AddKeyboardEventHandler(std::function<void (WMKeyboardEvent)> handler)
{
    return nullptr;
}
#endif // __APPLE__
