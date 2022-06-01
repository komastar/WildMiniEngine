#pragma once
#include "d3d12_include.h"
#include "Graphics/WMCommandList.h"

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
        virtual void Close() override;
        virtual void Reset() override;
    };
}
