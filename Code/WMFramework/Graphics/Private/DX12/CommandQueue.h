#pragma once
#include "d3d12_include.h"
#include "Graphics/WMCommandQueue.h"

namespace WildMini::Graphics::Private::DX12
{
    class CommandQueue : public WMCommandQueue
    {
    public:
        CommandQueue(ID3D12Device* device);

        ID3D12CommandQueue* Get();

    private:
        ComPtr<ID3D12CommandQueue> commandQueue;
    };
}
