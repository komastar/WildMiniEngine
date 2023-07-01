//
//  File:   WMImage.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMSharedPtr.h"
#include "Graphics/WMGraphicsDevice.h"
#include "Graphics/WMTexture.h"
#include "Graphics/Primitive/WMSize.h"

namespace WildMini
{
    class WM_API WMImage
    {

    public:
        WMImage();
        WMImage(const uint32_t);
        WMImage(const WMSize&);
        WMImage(WMSharedPtr<WMTexture>);
        virtual ~WMImage();

    public:
        bool Create(WMGraphicsDevice*, const std::wstring&);
        WMSharedPtr<WMTexture> GetTexture();

    private:
        WMSharedPtr<WMTexture> texture;
    };
}
