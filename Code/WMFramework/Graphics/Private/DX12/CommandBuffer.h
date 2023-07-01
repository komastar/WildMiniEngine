//
//  File:   CommandBuffer.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "d3d12_include.h"
#include "Graphics/WMCommandBuffer.h"
#include "Graphics/Private/DX12/RenderCommandEncoder.h"
#include "Graphics/Private/DX12/CopyCommandEncoder.h"
#include "CommandQueue.h"

namespace WildMini
{
    class CommandBuffer : public WMCommandBuffer
    {
    public:
        CommandBuffer(ID3D12DescriptorHeap*, CommandQueue*, ID3D12CommandAllocator*, ID3D12GraphicsCommandList*, D3D12_COMMAND_LIST_TYPE);
        virtual ~CommandBuffer();

        virtual WMSharedPtr<WMRenderCommandEncoder> CreateRenderCommandEncoder(WMRenderPipeline* renderPipeline) override;
        virtual WMSharedPtr<WMCopyCommandEncoder> CreateCopyCommandEncoder() override;
        virtual void Commit() override;
        void AddEncodedCommandList(ID3D12GraphicsCommandList* commandList);

    protected:
        WMSharedPtr<CommandQueue> commandQueue;
        ComPtr<ID3D12GraphicsCommandList> commandList;
        ComPtr<ID3D12CommandAllocator> commandAllocator;
        ComPtr<ID3D12Device> device;
        //ComPtr<ID3D12DescriptorHeap> imguiDescHeap;
        D3D12_COMMAND_LIST_TYPE type;
    };
}
