#pragma once
#include "Graphics/Platform/DX/d3d12_include.h"
#include "Graphics/WMCommandList.h"

namespace WildMini::Graphics
{
    class WMCommandListImpl : public WMCommandList
    {
    public:
        WMCommandListImpl(ID3D12Device* device, ID3D12CommandAllocator* commandAllocator);

    private:
        ComPtr<ID3D12GraphicsCommandList> commandList;
        ComPtr<ID3D12CommandAllocator> commandAllocator;

    public:
        virtual void Close() override;
        virtual void Reset() override;
    };
}
