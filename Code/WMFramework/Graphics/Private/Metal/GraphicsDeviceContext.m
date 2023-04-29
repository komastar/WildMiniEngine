//
//  GraphicsDeviceContext.m
//  WMFramework
//
//  Created by Eugene Kim on 2022/08/20.
//

#import <Foundation/Foundation.h>
#include "GraphicsDeviceContext.h"

using namespace WildMini;

WMSharedPtr<WMCommandQueue> GraphicsDeviceContext::CreateCommandQueue()
{
    return nullptr;
}

WMSharedPtr<WMGPUBuffer> GraphicsDeviceContext::CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode)
{
    return nullptr;
}

WMSharedPtr<WMTexture> GraphicsDeviceContext::CreateTexture(const WMTexture::Desc &desc)
{
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
