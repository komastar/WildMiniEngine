#pragma once
#include "Graphics/ITexture.h"

namespace Core
{
    class Texture : public ITexture
    {
        virtual size_t Size() const override;
        virtual uint32_t Width() const override;
        virtual uint32_t Height() const override;
        virtual PixelFormat Format() const override;
    };
}
