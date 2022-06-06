//
//  WindowContext.h
//  WMFramework
//
//  Created by Eugene Kim on 2022/06/06.
//

#ifdef __APPLE__
#include <Cocoa/Cocoa.h>
#include "Window/WMWindow.h"

namespace WildMini::Window
{
    class WindowContext : public WMWindow
    {
    public:
        WindowContext();
        
    public:
        virtual void Create() override;
        virtual void Show() override;
        virtual void Hide() override;
        virtual void Update() override;
        virtual void Focus() override;

        virtual void* PlatformHandle() override;

        virtual uint32_t Width() override;
        virtual uint32_t Height() override;
        
    private:
        NSWindow* window;
        NSView* view;
    };
}
#endif /* __APPLE__ */
