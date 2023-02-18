//
//  File:   CopyCommandEncoder.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "d3d12_include.h"
#include "Graphics/WMCopyCommandEncoder.h"
#include "CommandBuffer.h"

namespace WildMini::Graphics::Private::DX12
{
    class CopyCommandEncoder : public WMCopyCommandEncoder
    {
    public:
        CopyCommandEncoder(CommandBuffer* _commandBuffer, ID3D12GraphicsCommandList* _commandList);
        virtual ~CopyCommandEncoder();

    public:
        virtual void CopyBufferToBuffer(WMGPUBuffer* src, size_t srcOffset, WMGPUBuffer* dest, size_t destOffset, size_t copySize) override;
        virtual void CopyBufferToTexture(WMGPUBuffer* src, size_t srcOffset, WMTexture* dest, TextureArea destArea) override;
        virtual void CopyTextureToBuffer(WMTexture* src, TextureArea srcArea, WMGPUBuffer* dest, size_t destOffset) override;
        virtual void EndEncoding() override;

    private:
        void TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before);

        WildMini::WMSharedPtr<CommandBuffer> commandBuffer;
        ComPtr<ID3D12GraphicsCommandList> commandList;
    };
}
