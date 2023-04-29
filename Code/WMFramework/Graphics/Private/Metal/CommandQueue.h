//
//  CommandQueue.h
//  WMFramework
//
//  Created by Eugene Kim on 2023/04/29.
//

#ifdef __APPLE__
#ifndef CommandQueue_h
#define CommandQueue_h
#import <Metal/Metal.h>
#include "Graphics/WMGraphicsDevice.h"
#include "Graphics/WMCommandQueue.h"

namespace WildMini
{
    class CommandQueue : public WMCommandQueue
    {
    public:
        CommandQueue(WMGraphicsDevice*, id<MTLCommandQueue>);
        ~CommandQueue();
        
    public:
        WMSharedPtr<WildMini::WMSwapChain> CreateSwapChain(WildMini::WMWindow *) override;
        WMSharedPtr<WildMini::WMCommandBuffer> CreateCommandBuffer() override;
        void WaitComplete() override;
        
        id<MTLCommandQueue> mtlCommandQueue;
    };
}
#endif /* CommandQueue_h */
#endif /* __APPLE__ */
