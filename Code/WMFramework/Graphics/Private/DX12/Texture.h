#pragma once
#include "d3d12_include.h"
#include "Graphics/WMTexture.h"

namespace WildMini::Graphics::Private::DX12
{
    inline uint32_t PixelFormatSize(WMPixelFormat format)
    {
        switch (format)
        {
        case WildMini::Graphics::RGBA_8_UNML:
        case WildMini::Graphics::RGBA_8_SNML:
        case WildMini::Graphics::RGBA_8_UINT:
        case WildMini::Graphics::RGBA_8_SINT:
        case WildMini::Graphics::DEPTH_24_UNORM_STENCIL_8:
            return 4;
        default:
            break;
        }

        return 0;
    }

    inline WMPixelFormat PixelFormat(DXGI_FORMAT format)
    {
        switch (format)
        {
        case DXGI_FORMAT_R8G8B8A8_UNORM:
            return WMPixelFormat::RGBA_8_UNML;
        case DXGI_FORMAT_R8G8B8A8_SNORM:
            return WMPixelFormat::RGBA_8_SNML;
        case DXGI_FORMAT_R8G8B8A8_UINT:
            return WMPixelFormat::RGBA_8_UINT;
        case DXGI_FORMAT_R8G8B8A8_SINT:
            return WMPixelFormat::RGBA_8_SINT;
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
            return WMPixelFormat::DEPTH_24_UNORM_STENCIL_8;
        }

        return WMPixelFormat::NONE;
    }

    inline DXGI_FORMAT PixelFormat(WMPixelFormat format)
    {
        switch (format)
        {
        case WMPixelFormat::RGBA_8_UNML:
            return DXGI_FORMAT_R8G8B8A8_UNORM;
        case WMPixelFormat::RGBA_8_SNML:
            return DXGI_FORMAT_R8G8B8A8_SNORM;
        case WMPixelFormat::RGBA_8_UINT:
            return DXGI_FORMAT_R8G8B8A8_UINT;
        case WMPixelFormat::RGBA_8_SINT:
            return DXGI_FORMAT_R8G8B8A8_SINT;
        case WMPixelFormat::DEPTH_24_UNORM_STENCIL_8:
            return DXGI_FORMAT_D24_UNORM_S8_UINT;
        }

        return DXGI_FORMAT_UNKNOWN;
    }

    class Texture : public WMTexture
    {
    public:
        Texture(ID3D12Resource* buffer, D3D12_RESOURCE_STATES state);

    public:
        virtual size_t Size() const override;
        virtual uint32_t Width() const override;
        virtual uint32_t Height() const override;
        virtual WMPixelFormat Format() const override;

        D3D12_CPU_DESCRIPTOR_HANDLE renderTargetView;

    private:
        size_t size;
        uint32_t width;
        uint32_t height;
        WMPixelFormat format;
        ComPtr<ID3D12Resource> buffer;
        D3D12_RESOURCE_STATES state;
    };
}
