//
//  GPUBuffer.m
//  WMFramework
//
//  Created by Eugene Kim on 2023/04/29.
//

#import <Foundation/Foundation.h>
#include "Graphics/Private/Metal/GPUBuffer.h"

using namespace WildMini;

GPUBuffer::GPUBuffer(id<MTLBuffer> buffer)
{
    mtlBuffer = [buffer retain];
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
    return false;
}

bool GPUBuffer::IsReadable() const
{
    return false;
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
