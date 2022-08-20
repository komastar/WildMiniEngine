//
//  GraphicsDeviceContext.m
//  WMFramework
//
//  Created by Eugene Kim on 2022/08/20.
//

#import <Foundation/Foundation.h>
#include "GraphicsDeviceContext.h"

using namespace WildMini::Graphics;
using namespace WildMini::Graphics::Private;
using namespace WildMini::Object;

WMObject<WMCommandQueue> GraphicsDeviceContext::CreateCommandQueue()
{
    return nullptr;
}

WMObject<WMGPUBuffer> GraphicsDeviceContext::CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode)
{
    return nullptr;
}

WMObject<WMTexture> GraphicsDeviceContext::CreateTexture(const WMTexture::Desc &desc)
{
    return nullptr;
}

WMObject<WMRenderPipeline> GraphicsDeviceContext::CreateRenderPipeline(const WildMini::Graphics::WMRenderPipelineDescriptor &desc)
{
    return nullptr;
}

WMObject<WMShader> GraphicsDeviceContext::CreateShader(const std::vector<uint8_t> &data, const std::string &entry, WMShader::StageType stage)
{
    return nullptr;
}
