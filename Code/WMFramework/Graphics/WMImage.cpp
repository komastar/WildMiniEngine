//
//  File:   WMImage.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#include "Graphics/WMImage.h"
#include "Graphics/WMCommandQueue.h"
#include "Graphics/WMCommandBuffer.h"
#include "IO/File/WMFile.h"
#include "png.h"
#include "pngstruct.h"
#include "pnginfo.h"

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

bool WMImage::Create(WMGraphicsDevice* device, const std::wstring& InFilePath)
{
    FILE* pngFile = nullptr;
    std::string filepath(InFilePath.begin(), InFilePath.end());
    fopen_s(&pngFile, filepath.c_str(), "rb");

    if (!pngFile)
    {
        return false;
    }

    unsigned char header[8]{ 0 };
    fread_s(header, 8, 1, 8, pngFile);

    if (png_sig_cmp(header, 0, 8))
    {
        return false;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        return false;
    }

    png_infop info_ptr = nullptr;
    info_ptr = png_create_info_struct(png_ptr);

    png_init_io(png_ptr, pngFile);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);
    png_set_alpha_mode(png_ptr, PNG_ALPHA_PNG, PNG_GAMMA_sRGB);
    auto width = png_get_image_width(png_ptr, info_ptr);
    auto height = png_get_image_height(png_ptr, info_ptr);
    auto color_type = png_get_color_type(png_ptr, info_ptr);
    auto bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    png_read_update_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        return false;
    }

    png_bytepp row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (size_t i = 0; i < height; i++)
    {
        row_pointers[i] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));
    }

    png_read_image(png_ptr, row_pointers);

    Vector<uint8_t> rowData(height * info_ptr->rowbytes, 0);
    for (size_t i = 0; i < height; i++)
    {
        memcpy(rowData.data() + (i * info_ptr->rowbytes), row_pointers[i], info_ptr->rowbytes);
    }

    fclose(pngFile);

    WMTexture::Desc desc;
    desc.width = info_ptr->width;
    desc.height = info_ptr->height;
    texture = device->CreateTexture(desc);

    if (WMSharedPtr<WMCommandQueue> commandQueue = device->CreateCommandQueue())
    {
        if (WMSharedPtr<WMCommandBuffer> commandBuffer = commandQueue->CreateCommandBuffer())
        {
            if (WMSharedPtr<WMCopyCommandEncoder> encoder = commandBuffer->CreateCopyCommandEncoder())
            {
                WMSharedPtr<WMGPUBuffer> buffer = device->CreateGPUBuffer(texture->Size(), WMGPUBuffer::CPUCacheMode::WRITABLE);
                WMCopyCommandEncoder::TextureArea area(0, 0, width, height);
                encoder->CopyBufferToTexture(buffer, 0, texture, area);

                return true;
            }
        }
    }

    return false;
}

WMSharedPtr<WMTexture> WMImage::GetTexture()
{
    return texture;
}
