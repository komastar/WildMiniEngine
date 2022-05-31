#pragma once
#include "Graphics/Platform/DX/d3d12_include.h"
#include "Graphics/WMCommandQueue.h"

namespace WildMini::Graphics
{
    class WMCommandQueueImpl : public WMCommandQueue
    {
    public:
        WMCommandQueueImpl(ID3D12Device* device);

        ID3D12CommandQueue* Get();

    private:
        ComPtr<ID3D12CommandQueue> commandQueue;
    };
}
