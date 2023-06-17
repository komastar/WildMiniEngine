//
//  File:   WMImage.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#include "Graphics/WMImage.h"
#include "IO/File/WMFile.h"

using namespace WildMini;

WMImage::WMImage()
{
}

WMImage::WMImage(const uint32_t size)
{
}

WMImage::WMImage(const WMSize& size)
{
}

WMImage::WMImage(WMSharedPtr<WMTexture> InTexture)
{
}

WMImage::~WMImage()
{
}

bool WMImage::Create(const std::wstring& InFilePath)
{
    WMSharedPtr<WMFile> file = WMFile::Open(InFilePath, WMFile::AccessMode::ReadOnly, WMFile::OpenMode::Exisiting, true);
    return false;
}
