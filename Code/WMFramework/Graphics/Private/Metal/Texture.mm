//
//  Texture.m
//  WMFramework
//
//  Created by Eugene Kim on 2023/04/29.
//

#import <Foundation/Foundation.h>
#include "Graphics/Private/Metal/Texture.h"

using namespace WildMini;

Texture::Texture(id<MTLTexture> texture)
{
    mtlTexture = [texture retain];
}

Texture::~Texture()
{ 

}

uint32_t Texture::Height() const { 
    return 0;
}


uint32_t Texture::Width() const { 
    return 0;
}

WMPixelFormat Texture::Format() const {
    return WMPixelFormat::NONE;
}

size_t Texture::Size() const { 
    return 0;
}




