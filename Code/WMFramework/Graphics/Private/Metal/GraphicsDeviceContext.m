//
//  GraphicsDeviceContext.m
//  WMFramework
//
//  Created by Eugene Kim on 2022/08/20.
//

#import <Foundation/Foundation.h>
#include "GraphicsDeviceContext.h"
#include "Graphics/Private/Metal/CommandQueue.h"
#include "Graphics/Private/Metal/GPUBuffer.h"
#include "Graphics/Private/Metal/Texture.h"

using namespace WildMini;

WMSharedPtr<WMCommandQueue> GraphicsDeviceContext::CreateCommandQueue()
{
    id<MTLCommandQueue> mtlCommandQueue = [mtlDevice newCommandQueue];
    return new CommandQueue(this, [mtlCommandQueue autorelease]);
}

WMSharedPtr<WMGPUBuffer> GraphicsDeviceContext::CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode)
{
    if (size > 0)
    {
        MTLResourceOptions resourceOption = 0;
        switch (mode)
        {
            case WMGPUBuffer::CPUCacheMode::NONE:
            case WMGPUBuffer::CPUCacheMode::READABLE:
                resourceOption |= MTLResourceCPUCacheModeDefaultCache;
                break;
            case WMGPUBuffer::CPUCacheMode::WRITABLE:
                resourceOption |= MTLResourceCPUCacheModeWriteCombined;
                break;
        }

        @autoreleasepool {
            id<MTLBuffer> buffer = [mtlDevice newBufferWithLength:size options:resourceOption];
            if (buffer) {
                return new GPUBuffer(buffer);
            }
        }
    }

    return nullptr;
}

WMSharedPtr<WMTexture> GraphicsDeviceContext::CreateTexture(const WMTexture::Desc &desc)
{
    @autoreleasepool {
        MTLTextureDescriptor* texDesc = [[[MTLTextureDescriptor alloc] init] autorelease];
        id<MTLTexture> texture = [mtlDevice newTextureWithDescriptor:texDesc];
        return new Texture([texture autorelease]);
    }
    return nullptr;
}

WMSharedPtr<WMRenderPipeline> GraphicsDeviceContext::CreateRenderPipeline(const WMRenderPipelineDescriptor &desc)
{
    return nullptr;
}

WMSharedPtr<WMShader> GraphicsDeviceContext::CreateShader(const std::vector<uint8_t> &data, const std::string &entry, WMShader::StageType stage)
{
    return nullptr;
}
