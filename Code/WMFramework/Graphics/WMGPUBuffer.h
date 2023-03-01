//
//  File:   WMGPUBuffer.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMRefCounter.h"

namespace WildMini
{
    class WM_API WMGPUBuffer : public WMRefCounter
    {
    public:
        enum class CPUCacheMode
        {
            NONE = 0,
            WRITABLE,
            READABLE
        };

    public:
        WMGPUBuffer() = default;

    public:
        virtual size_t Size() const = 0;
        virtual bool IsWritable() const = 0;
        virtual bool IsReadable() const = 0;
        virtual bool WriteData(const void* data, size_t size) = 0;
        virtual bool WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize) = 0;
        virtual bool ReadData(void* data, size_t size) = 0;
    };
}
