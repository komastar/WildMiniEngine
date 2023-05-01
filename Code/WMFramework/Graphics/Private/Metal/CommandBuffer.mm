//
//  CommandBuffer.m
//  WMFramework
//
//  Created by Eugene Kim on 2023/04/29.
//

#include "CommandBuffer.h"
#include "Graphics/Private/Metal/RenderCommandEncoder.h"

using namespace WildMini;

CommandBuffer::CommandBuffer(CommandQueue* commandBuffer)
{
}

CommandBuffer::~CommandBuffer()
{
}

WMSharedPtr<WMRenderCommandEncoder> CommandBuffer::CreateRenderCommandEncoder(WMRenderPipeline *renderPipeline)
{
    return new RenderCommandEncoder();
}

void CommandBuffer::Commit()
{
}
