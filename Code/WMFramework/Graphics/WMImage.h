//
//  File:   WMImage.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMSharedPtr.h"
#include "Graphics/WMTexture.h"
#include "Graphics/Primitive/WMSize.h"

namespace WildMini
{
    class WMImage
    {
    public:
        WMImage();
        WMImage(const uint32_t);
        WMImage(const WMSize&);
        WMImage(WMSharedPtr<WMTexture>);
        virtual ~WMImage();

    public:
        bool Create(const std::wstring&);

    private:
        WMSharedPtr<WMTexture> texture;
    };
}
