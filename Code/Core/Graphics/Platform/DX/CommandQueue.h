#pragma once
#include "Graphics/Platform/DX/d3d12_include.h"
#include "Graphics/ICommandQueue.h"

namespace Core
{
    class CommandQueue : public ICommandQueue
    {
    public:
        CommandQueue(ID3D12Device* device);

        ID3D12CommandQueue* Get();

    private:
        ComPtr<ID3D12CommandQueue> commandQueue;
    };
}
