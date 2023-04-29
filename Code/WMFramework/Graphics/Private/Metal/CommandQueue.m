//
//  CommandQueue.m
//  WMFramework
//
//  Created by Eugene Kim on 2023/04/29.
//

#import <Foundation/Foundation.h>
#include "Graphics/Private/Metal/CommandQueue.h"
#include "Graphics/Private/Metal/CommandBuffer.h"
#include "Graphics/Private/Metal/SwapChain.h"

using namespace WildMini;


CommandQueue::CommandQueue(WMGraphicsDevice* device, id<MTLCommandQueue> commandQueue)
{
    mtlCommandQueue = [commandQueue retain];
}

CommandQueue::~CommandQueue()
{
    [mtlCommandQueue autorelease];
}

WMSharedPtr<WMSwapChain> CommandQueue::CreateSwapChain(WMWindow* window)
{
    return new SwapChain(this, nullptr);
}

WMSharedPtr<WMCommandBuffer> CommandQueue::CreateCommandBuffer()
{
    return new CommandBuffer(this);
}

void CommandQueue::WaitComplete()
{
}
