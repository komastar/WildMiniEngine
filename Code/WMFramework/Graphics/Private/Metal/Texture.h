//
//  Texture.h
//  WMFramework
//
//  Created by Eugene Kim on 2023/04/29.
//

#ifdef __APPLE__
#ifndef Texture_h
#define Texture_h
#import <Metal/Metal.h>
#include "Graphics/WMTexture.h"

namespace WildMini
{
    class Texture : public WMTexture
    {
    public:
    Texture(id<MTLTexture>);
    ~Texture();

    size_t Size() const override;
    uint32_t Width() const override;
    uint32_t Height() const override;
    WMPixelFormat Format() const override;

    private:
    id<MTLTexture> mtlTexture;
    };
}

#endif /* Texture_h */
#endif /* __APPLE__ */
