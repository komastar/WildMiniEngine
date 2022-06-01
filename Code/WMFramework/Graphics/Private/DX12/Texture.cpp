#include "Texture.h"

using namespace WildMini::Graphics;
using namespace WildMini::Graphics::Private::DX12;

Texture::Texture(ID3D12Resource* buffer, D3D12_RESOURCE_STATES state)
    : buffer(buffer)
    , state(state)
{
    D3D12_RESOURCE_DESC desc = buffer->GetDesc();
    width = static_cast<uint32_t>(desc.Width);
    height = static_cast<uint32_t>(desc.Height);
    format = PixelFormat(desc.Format);
    size = AlignTextureRowPitch(width * PixelFormatSize(format)) * height;
}

size_t Texture::Size() const
{
    return size;
}

uint32_t Texture::Width() const
{
    return width;
}

uint32_t Texture::Height() const
{
    return height;
}

WMPixelFormat Texture::Format() const
{
    return format;
}
