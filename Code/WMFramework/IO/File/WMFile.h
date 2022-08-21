//
//  File:   WMFile.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Object/WMObject.h"
#include "IO/File/WMFileHandle.h"

namespace WildMini::IO::File
{
    class WM_API WMFile : public WildMini::Object::WMRefCounter
    {
    public:
        enum class OpenMode
        {
            Exisiting = 0,
            Truncate,
            Append
        };

        enum class AccessMode
        {
            ReadOnly = 0,
            WriteOnly,
            ReadWrite
        };

        enum class SeekOrigin
        {
            Start,
            End,
            Current
        };

        static WildMini::Object::WMObject<WMFile> Open(const std::wstring& path, WMFile::AccessMode accessMode, WMFile::OpenMode openMode, bool binary);
        static WildMini::Object::WMObject<WMFile> OpenText(const std::wstring& path, WMFile::AccessMode accessMode, WMFile::OpenMode openMode);
        static WildMini::Object::WMObject<WMFile> OpenBinary(const std::wstring& path, WMFile::AccessMode accessMode, WMFile::OpenMode openMode);

        static bool Delete(const std::wstring& path);
        static bool IsExist(const std::wstring& path);

        ~WMFile();

        size_t Read(void* buffer, size_t byteToRead) const;
        size_t Write(const void* buffer, size_t byteToWrite);
        size_t Seek(size_t offset, SeekOrigin seekOrigin = SeekOrigin::Start);

        size_t CurrentPosition() const;
        size_t TotalLength() const;
        size_t RemainLength() const;

        const std::wstring& Filename() const;
        const std::wstring& Extension() const;
        const std::wstring& RelativePath() const;
        const std::wstring& AbsolutePath() const;

    private:
        WMFile();
        WMFile(const WMFile& file) = delete;
        WMFile& operator=(const WMFile& file) = delete;

        WMFileHandle* impl;
        size_t fileSize;
        std::wstring filename;
        std::wstring extension;
        std::wstring relativePath;
        std::wstring absolutePath;
    };
}
