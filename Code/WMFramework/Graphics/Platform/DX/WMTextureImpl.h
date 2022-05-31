#pragma once
#include "Graphics/WMTexture.h"

namespace WildMini::Graphics
{
    class WMTextureImpl : public WMTexture
    {
        virtual size_t Size() const override;
        virtual uint32_t Width() const override;
        virtual uint32_t Height() const override;
        virtual PixelFormat Format() const override;
    };
}
