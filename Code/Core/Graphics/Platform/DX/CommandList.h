#pragma once
#include "Graphics/Platform/DX/d3d12_include.h"
#include "Graphics/ICommandList.h"
#include "CommandAllocator.h"

namespace Core
{
    class CommandList : public ICommandList, public RefCounter
    {
    public:
        CommandList(ID3D12Device* device, CommandAllocator* commandAllocator);

        void Close();
        void Reset();

    private:
        ComPtr<ID3D12GraphicsCommandList> commandList;
        ComPtr<ID3D12CommandAllocator> commandAllocator;
    };
}
