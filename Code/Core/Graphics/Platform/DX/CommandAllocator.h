#pragma once
#include "Graphics/Platform/DX/d3d12_include.h"

namespace Core
{
    class CommandAllocator : public RefCounter
    {
    public:
        CommandAllocator(ID3D12Device* device);

        ID3D12CommandAllocator* Get()
        {
            return commandAllocator.Get();
        }

    private:
        ComPtr<ID3D12CommandAllocator> commandAllocator;
    };
}
