#pragma once
#include "Common/RefCounter.h"

namespace Core
{
    enum PixelFormat
    {
        RGBA = 0
    };

    class ITexture : public RefCounter
    {
    public:
        virtual size_t Size() const = 0;
        virtual uint32_t Width() const = 0;
        virtual uint32_t Height() const = 0;
        virtual PixelFormat Format() const = 0;
    };
}
