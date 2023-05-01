//
//  GPUBuffer.m
//  WMFramework
//
//  Created by Eugene Kim on 2023/04/29.
//

#import <Foundation/Foundation.h>
#include "Graphics/Private/Metal/GPUBuffer.h"

using namespace WildMini;

GPUBuffer::GPUBuffer(id<MTLBuffer> buffer, WMGPUBuffer::CPUCacheMode inMode)
{
    mtlBuffer = [buffer retain];
    mode = inMode;
}

GPUBuffer::~GPUBuffer()
{
    [mtlBuffer release];
}

size_t GPUBuffer::Size() const
{
    return mtlBuffer.length;
}

bool GPUBuffer::IsWritable() const
{
    return (mode == WMGPUBuffer::CPUCacheMode::WRITABLE);
}

bool GPUBuffer::IsReadable() const
{
    return (mode == WMGPUBuffer::CPUCacheMode::READABLE);
}

bool GPUBuffer::WriteData(const void *data, size_t size)
{
    return false;
}

bool GPUBuffer::WriteDataForTexture(const void *data, uint32_t width, uint32_t height, uint32_t formatSize)
{
    return false;
}

bool GPUBuffer::ReadData(void *data, size_t size)
{
    return false;
}
