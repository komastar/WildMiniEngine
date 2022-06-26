//
//  File:   WMFile.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMFile.h"
#include "IO/File/Private/FileHandle.h"

using namespace WildMini::Object;
using namespace WildMini::IO::File;
using namespace WildMini::IO::File::Private;

WMFile::WMFile()
    : fileSize(0)
    , impl(nullptr)
{
}

WMFile::~WMFile()
{
    if (impl)
    {
        auto handle = reinterpret_cast<Private::FileHandle*>(impl);
        handle->stream.close();

        delete impl;
        impl = nullptr;
    }
}

WMObject<WMFile> WMFile::Open(const std::wstring& path, WMFile::AccessMode accessMode, WMFile::OpenMode openMode, bool binary)
{
    std::ios_base::openmode mode = std::ios_base::in;
    switch (accessMode)
    {
    case WMFile::AccessMode::WriteOnly:
        mode = std::ios_base::out;
        break;
    case WMFile::AccessMode::ReadWrite:
        mode = std::ios_base::in | std::ios_base::out;
        break;
    }

    if (WMFile::AccessMode::ReadOnly != accessMode)
    {
        switch (openMode)
        {
        case WMFile::OpenMode::Truncate:
            mode |= std::ios_base::trunc;
            break;
        case WMFile::OpenMode::Append:
            mode |= std::ios_base::app;
            break;
        }
    }

    if (binary)
    {
        mode |= std::ios_base::binary;
    }

    std::fstream stream(path, mode);
    if (stream.is_open())
    {
        WMFile* file = new WMFile();
        file->impl = new FileHandle(stream);
        Private::FileHandle* fileHandle = reinterpret_cast<Private::FileHandle*>(file->impl);
        std::filesystem::path fsPath(path.data());
        file->filename = fsPath.filename().c_str();
        file->extension = fsPath.extension().c_str();
        file->absolutePath = std::filesystem::canonical(fsPath).c_str();
        file->relativePath = fsPath.relative_path().c_str();
        file->fileSize = std::filesystem::file_size(fsPath);

        return file;
    }
    return nullptr;
}

WMObject<WMFile> WMFile::OpenText(const std::wstring& path, AccessMode accessMode, OpenMode openMode)
{
    return WMFile::Open(path, accessMode, openMode, false);
}

WMObject<WMFile> WMFile::OpenBinary(const std::wstring& path, AccessMode accessMode, OpenMode openMode)
{
    return WMFile::Open(path, accessMode, openMode, true);
}

bool WMFile::Delete(const std::wstring& path)
{
    if (WMFile::IsExist(path))
    {
        return std::filesystem::remove(std::filesystem::path(path.data()));
    }
    return false;
}

bool WMFile::IsExist(const std::wstring& path)
{
    auto fsPath = std::filesystem::path(path.data());
    return std::filesystem::exists(fsPath) && std::filesystem::is_regular_file(fsPath);
}

size_t WMFile::Read(void* buffer, size_t byteToRead) const
{
    size_t readableSize = Min(byteToRead, RemainLength());
    if (0 < readableSize)
    {
        impl->stream.read(reinterpret_cast<char*>(buffer), readableSize);
    }

    return readableSize;
}

size_t WMFile::Write(const void* buffer, size_t byteToWrite)
{
    impl->stream.write(reinterpret_cast<const char*>(buffer), byteToWrite);
    impl->stream.flush();
    size_t currentPosition = CurrentPosition();
    if (fileSize < currentPosition)
    {
        fileSize = currentPosition;
    }

    return byteToWrite;
}

size_t WMFile::Seek(size_t offset, SeekOrigin seekOrigin /*= SeekOrigin::Start*/)
{
    std::ios_base::seekdir dir = std::ios_base::beg;
    switch (seekOrigin)
    {
    case WMFile::SeekOrigin::Current:
        dir = std::ios_base::cur;
        break;
    case WMFile::SeekOrigin::End:
        dir = std::ios_base::end;
        break;
    }

    impl->stream.seekg(offset, dir);
    return impl->stream.tellg();
}

size_t WMFile::CurrentPosition() const
{
    return impl->stream.tellg();
}

size_t WMFile::TotalLength() const
{
    return fileSize;
}

size_t WMFile::RemainLength() const
{
    size_t currentPosition = CurrentPosition();
    if (fileSize < currentPosition)
    {
        return 0;
    }

    return fileSize - currentPosition;
}

const std::wstring& WMFile::Filename() const
{
    return filename;
}

const std::wstring& WMFile::Extension() const
{
    return extension;
}

const std::wstring& WMFile::RelativePath() const
{
    return relativePath;
}

const std::wstring& WMFile::AbsolutePath() const
{
    return absolutePath;
}
