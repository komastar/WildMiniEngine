//
//  File:   CommandQueue.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "d3d12_include.h"
#include "Graphics/WMCommandQueue.h"

#include "GraphicsDeviceContext.h"

namespace WildMini::Graphics::Private::DX12
{
    class CommandQueue : public WMCommandQueue
    {
    public:
        CommandQueue(GraphicsDeviceContext*, ID3D12CommandQueue*, ID3D12CommandAllocator*, ID3D12GraphicsCommandList*, ID3D12Fence*);

        virtual WildMini::WMSharedPtr<Graphics::WMSwapChain> CreateSwapChain(Window::WMWindow*) override;
        virtual WildMini::WMSharedPtr<WMCommandBuffer> CreateCommandBuffer() override;

        void WaitComplete() override;

        ID3D12CommandQueue* Queue() const { return commandQueue.Get(); }

        uint64_t ExecuteCommandLists(uint32_t numCommandLists, ID3D12CommandList* const* commandLists);

    private:
        WildMini::WMSharedPtr<GraphicsDeviceContext> device;
        ComPtr<ID3D12CommandQueue> commandQueue;
        ComPtr<ID3D12Fence> fence;
        ComPtr<ID3D12CommandAllocator> commandAllocator;
        ComPtr<ID3D12GraphicsCommandList> commandList;
        UINT64 fenceNumber;
    };
}
