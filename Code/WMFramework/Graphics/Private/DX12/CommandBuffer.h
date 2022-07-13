//
//  File:   CommandBuffer.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "d3d12_include.h"
#include "Graphics/WMCommandBuffer.h"
#include "Graphics/WMRenderCommandEncoder.h"
#include "RenderCommandEncoder.h"
#include "CommandQueue.h"

namespace WildMini::Graphics::Private::DX12
{
    class CommandBuffer : public WMCommandBuffer
    {
    public:
        CommandBuffer(CommandQueue*, ID3D12CommandAllocator*, ID3D12GraphicsCommandList*, D3D12_COMMAND_LIST_TYPE);

        virtual Object::WMObject<WMRenderCommandEncoder> CreateRenderCommandEncoder(WMRenderPipeline* renderPipeline) override;
        virtual void Commit() override;
        void AddEncodedCommandList(ID3D12GraphicsCommandList* commandList);

    protected:
        Object::WMObject<CommandQueue> commandQueue;
        ComPtr<ID3D12GraphicsCommandList> commandList;
        ComPtr<ID3D12CommandAllocator> commandAllocator;
        D3D12_COMMAND_LIST_TYPE type;
    };
}
