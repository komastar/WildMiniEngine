//
//  File:   WMGraphicsDevice.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMGraphicsDevice.h"
#include "Graphics/Private/GraphicsDeviceFactory.h"
#include "IO/File/WMFile.h"

using namespace WildMini;

namespace Private
{
    WMGraphicsDevice* device;
}

WMGraphicsDevice* WMGraphicsDevice::Get()
{
    if (!Private::device)
    {
        Private::device = GraphicsDeviceFactory::Create();
    }
    return Private::device;
}

WMSharedPtr<WMShader> WMGraphicsDevice::CreateShader(const std::wstring& path, const std::string& entry, WMShader::StageType stage)
{
    WMSharedPtr<WMFile> file = WMFile::OpenBinary(path, WMFile::AccessMode::ReadOnly, WMFile::OpenMode::Exisiting);
    if (file)
    {
        size_t fileLength = file->TotalLength();
        Vector<uint8_t> code(fileLength);
        file->Read(code.data(), fileLength);
        return CreateShader(code, entry, stage);
    }

    return nullptr;
}
