//
//  GraphicsDeviceContext.h
//  WMFramework
//
//  Created by Eugene Kim on 2022/08/20.
//

#ifdef __APPLE__
#ifndef GraphicsDeviceContext_h
#define GraphicsDeviceContext_h
#include "Graphics/WMGraphicsDevice.h"
#include "Graphics/WMCommandQueue.h"
#include "Graphics/WMGPUBuffer.h"
#include "Graphics/WMTexture.h"
#include "Graphics/WMRenderPipeline.h"
#include "Graphics/WMShader.h"

namespace WildMini
{
    class GraphicsDeviceContext : public WMGraphicsDevice
    {
        
        WMSharedPtr<WMCommandQueue> CreateCommandQueue() override;
        
        WMSharedPtr<WMGPUBuffer> CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode) override;
        
        WMSharedPtr<WMTexture> CreateTexture(const WMTexture::Desc &desc) override;
        
        WMSharedPtr<WMRenderPipeline> CreateRenderPipeline(const WMRenderPipelineDescriptor &desc) override;
        
        WMSharedPtr<WMShader> CreateShader(const std::vector<uint8_t> &data, const std::string &entry, WMShader::StageType stage) override;
        
    };
}
#endif /* GraphicsDeviceContext_h */
#endif // __APPLE__
