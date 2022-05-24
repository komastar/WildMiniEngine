#include "GPUBuffer.h"

size_t Core::GPUBuffer::Size() const
{
    return size_t();
}

bool Core::GPUBuffer::IsWritable() const
{
    return false;
}

bool Core::GPUBuffer::IsReadable() const
{
    return false;
}

bool Core::GPUBuffer::WriteData(const void* data, size_t size)
{
    return false;
}

bool Core::GPUBuffer::WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize)
{
    return false;
}

bool Core::GPUBuffer::ReadData(void* data, size_t size)
{
    return false;
}
