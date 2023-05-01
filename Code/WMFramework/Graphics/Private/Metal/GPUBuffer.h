//
//  GPUBuffer.h
//  WMFramework
//
//  Created by Eugene Kim on 2023/04/29.
//

#ifdef __APPLE__
#ifndef GPUBuffer_h
#define GPUBuffer_h
#import <Metal/Metal.h>
#include "Graphics/WMGraphicsDevice.h"
#include "Graphics/WMGPUBuffer.h"

namespace WildMini
{
    class GPUBuffer : public WMGPUBuffer
    {
    public:
        GPUBuffer(id<MTLBuffer>, WMGPUBuffer::CPUCacheMode);
        ~GPUBuffer();

    public:
        size_t Size() const override;
        bool IsWritable() const override;
        bool IsReadable() const override;
        bool WriteData(const void *data, size_t size) override;
        bool WriteDataForTexture(const void *data, uint32_t width, uint32_t height, uint32_t formatSize) override;
        bool ReadData(void *data, size_t size) override;

    private:
        id<MTLBuffer> mtlBuffer;
    WMGPUBuffer::CPUCacheMode mode;
    };
}

#endif /* GPUBuffer_h */
#endif /* __APPLE__ */
