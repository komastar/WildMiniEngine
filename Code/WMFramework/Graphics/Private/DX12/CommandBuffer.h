#pragma once
#include "d3d12_include.h"
#include "Graphics/WMCommandBuffer.h"
#include "CommandQueue.h"
#include "CommandList.h"

namespace WildMini::Graphics::Private::DX12
{
    class CommandBuffer : public WMCommandBuffer
    {
    public:
        virtual void CreateRenderCommandEncoder() override;
        virtual void Commit() override;

    protected:
        CommandQueue commandQueue;
        CommandList commandList;
        ComPtr<ID3D12CommandAllocator> commandAllocator;
    };
}
