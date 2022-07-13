//
//  File:   FileHandle.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
namespace WildMini::IO::File::Private
{
    struct FileHandle : public WildMini::IO::File::WMFileHandle
    {
        FileHandle(std::fstream& _stream)
        {
            _stream.swap(stream);
        }
    };
}
