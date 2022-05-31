#pragma once
#include "Graphics/WMGPUBuffer.h"

namespace WildMini::Graphics
{
    class WMGPUBufferImpl : public WMGPUBuffer
    {
        virtual size_t Size() const override;
        virtual bool IsWritable() const override;
        virtual bool IsReadable() const override;
        virtual bool WriteData(const void* data, size_t size) override;
        virtual bool WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize) override;
        virtual bool ReadData(void* data, size_t size) override;
    };
}
