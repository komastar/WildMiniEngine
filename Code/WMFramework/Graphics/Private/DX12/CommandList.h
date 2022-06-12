#pragma once
#include "d3d12_include.h"
#include "Graphics/WMCommandList.h"
#include "Graphics/WMTexture.h"

namespace WildMini::Graphics::Private::DX12
{
    class CommandList : public WMCommandList
    {
    public:
        CommandList(ID3D12Device* device, ID3D12CommandAllocator* commandAllocator);

    private:
        ComPtr<ID3D12GraphicsCommandList> commandList;
        ComPtr<ID3D12CommandAllocator> commandAllocator;

    public:
        virtual void SetViewport(const Primitive::WMViewport& viewport) override;
        virtual void SetScissorRect(const Primitive::WMRect& rect) override;
        virtual void SetRenderTarget(const WMTexture* renderTarget) override;
        virtual void ClearRenderTarget(const Graphics::WMTexture* renderTarget, const Primitive::WMColor& color) override;
        virtual void Close() override;
        virtual void Reset() override;
    };
}
