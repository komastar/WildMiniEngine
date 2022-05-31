#include "WMGPUBufferImpl.h"

using namespace WildMini::Graphics;

size_t WMGPUBufferImpl::Size() const
{
    return size_t();
}

bool WMGPUBufferImpl::IsWritable() const
{
    return false;
}

bool WMGPUBufferImpl::IsReadable() const
{
    return false;
}

bool WMGPUBufferImpl::WriteData(const void* data, size_t size)
{
    return false;
}

bool WMGPUBufferImpl::WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize)
{
    return false;
}

bool WMGPUBufferImpl::ReadData(void* data, size_t size)
{
    return false;
}
