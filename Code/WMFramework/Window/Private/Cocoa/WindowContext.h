//
//  WindowContext.h
//  WMFramework
//
//  Created by Eugene Kim on 2022/06/06.
//

#ifdef __APPLE__
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#include "Window/WMWindow.h"

namespace WildMini
{
    class WindowContext : public WMWindow
    {
    public:
        WindowContext(uint32_t _width, uint32_t _height);
        
    public:
        void Create() override;
        void Show() override;
        void Hide() override;
        void Update() override;
        void Focus() override;
        
        void SetTitle(const wchar_t *title) override;
        void *PlatformHandle() const override;
        float GetWidth() const override;
        float GetHeight() const override;
        void SetWidth(uint32_t width) override;
        void SetHeight(uint32_t height) override;
        void SetSize(uint32_t width, uint32_t height) override;
        float GetAspect() const override;
        void OnResize() override;
        void AddResizeCallback(std::function<void (uint32_t, uint32_t)> callback) override;
        
        WMWindow* AddMouseEventHandler(std::function<void (WMMouseEvent)> handler) override;
        WMWindow* AddKeyboardEventHandler(std::function<void (WMKeyboardEvent)> handler) override;
        
    private:
        NSWindow* window;
        NSView* view;
    };
}
#endif /* __APPLE__ */
