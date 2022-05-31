#pragma once
#include "Object/WMRefCounter.h"

namespace WildMini::Graphics
{
    enum PixelFormat
    {
        RGBA = 0
    };

    class WMTexture : public WildMini::Object::WMRefCounter
    {
    public:
        virtual size_t Size() const = 0;
        virtual uint32_t Width() const = 0;
        virtual uint32_t Height() const = 0;
        virtual PixelFormat Format() const = 0;
    };
}
