#pragma once
#ifdef _WIN32
#include "d3d12_include.h"

#include "Graphics/WMGraphicsDevice.h"

namespace WildMini::Graphics::Private
{
    class GraphicsDeviceContext : public WMGraphicsDevice
    {
    public:
        GraphicsDeviceContext();
        virtual ~GraphicsDeviceContext();

    private:
        ComPtr<IDXGIFactory4> dxgiFactory;
        ComPtr<ID3D12Device> device;

    public:
        virtual WildMini::Object::WMObject<WMCommandQueue> CreateCommandQueue() override;
        virtual WildMini::Object::WMObject<WMCommandList> CreateCommandList() override;
        virtual WildMini::Object::WMObject<WMGPUBuffer> CreateGPUBuffer(size_t size, WMGPUBuffer::CPUCacheMode mode) override;
        virtual WildMini::Object::WMObject<WMTexture> CreateTexture(const WMTexture::Desc& desc) override;
    };
}
#endif  //  _WIN32
