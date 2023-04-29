    //
    //  CommandBuffer.h
    //  WMFramework
    //
    //  Created by Eugene Kim on 2023/04/29.
    //

#ifdef __APPLE__
#ifndef CommandBuffer_h
#define CommandBuffer_h
#import <Metal/Metal.h>
#include "Graphics/WMCommandBuffer.h"
#include "Graphics/Private/Metal/CommandQueue.h"

namespace WildMini
{
    class CommandBuffer : public WMCommandBuffer
    {
    public:
        CommandBuffer(CommandQueue*);
        ~CommandBuffer();

    public:
        WMSharedPtr<WMRenderCommandEncoder> CreateRenderCommandEncoder(WMRenderPipeline *renderPipeline) override;
        void Commit() override;

    private:
        id<MTLCommandBuffer> mtlCommandBuffer;
    };
}

#endif /* CommandBuffer_h */
#endif /* __APPLE__ */

