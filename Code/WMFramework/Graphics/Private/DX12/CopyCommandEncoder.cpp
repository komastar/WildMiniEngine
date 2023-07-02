//
//  File:   CopyCommandEncoder.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "CopyCommandEncoder.h"
#include "Graphics/Private/DX12/CommandBuffer.h"
#include "GPUBuffer.h"
#include "Texture.h"
#include "Type.h"

using namespace WildMini;

CopyCommandEncoder::CopyCommandEncoder(WMCommandBuffer* _commandBuffer, ID3D12GraphicsCommandList* _commandList)
    : commandBuffer(_commandBuffer)
    , commandList(_commandList)
{
}

CopyCommandEncoder::~CopyCommandEncoder()
{
}

void CopyCommandEncoder::CopyBufferToBuffer(WMGPUBuffer* src, size_t srcOffset, WMGPUBuffer* dest, size_t destOffset, size_t copySize)
{
    GPUBuffer* srcBuffer = dynamic_cast<GPUBuffer*>(src);
    GPUBuffer* dstBuffer = dynamic_cast<GPUBuffer*>(dest);

    ID3D12Resource* srcRawBuffer = srcBuffer->Buffer();
    ID3D12Resource* dstRawBuffer = dstBuffer->Buffer();

    TransitionBufferState(dstRawBuffer, dstBuffer->InitialState(), D3D12_RESOURCE_STATE_COPY_DEST);
    commandList->CopyBufferRegion(dstRawBuffer, destOffset, srcRawBuffer, srcOffset, copySize);
    TransitionBufferState(dstRawBuffer, D3D12_RESOURCE_STATE_COPY_DEST, dstBuffer->InitialState());
}

void CopyCommandEncoder::CopyBufferToTexture(WMGPUBuffer* src, size_t srcOffset, WMTexture* dest, TextureArea destArea)
{
    GPUBuffer* srcBuffer = dynamic_cast<GPUBuffer*>(src);
    Texture* destTexture = dynamic_cast<Texture*>(dest);

    ID3D12Resource* gpuRawBuffer = srcBuffer->Buffer();
    ID3D12Resource* texRawBuffer = destTexture->Resource();

    TransitionBufferState(texRawBuffer, destTexture->InitialState(), D3D12_RESOURCE_STATE_COPY_DEST);

    D3D12_PLACED_SUBRESOURCE_FOOTPRINT bufferFootprint;
    
    D3D12_RESOURCE_DESC textureDesc = texRawBuffer->GetDesc();
    bufferFootprint.Offset = 0;
    bufferFootprint.Footprint.Format = textureDesc.Format;
    bufferFootprint.Footprint.Width = destArea.width;
    bufferFootprint.Footprint.Height = destArea.height;
    bufferFootprint.Footprint.Depth = textureDesc.DepthOrArraySize;
    bufferFootprint.Footprint.RowPitch = AlignTextureRowPitch(destArea.width * PixelFormatSize(destTexture->Format()));

    D3D12_BOX bufferBound;
    bufferBound.top = 0;
    bufferBound.bottom = destArea.height;
    bufferBound.left = static_cast<UINT>(srcOffset);
    bufferBound.right = destArea.width;
    bufferBound.front = 0;
    bufferBound.back = 1;

    CD3DX12_TEXTURE_COPY_LOCATION dstCopyLocation(texRawBuffer, 0);
    CD3DX12_TEXTURE_COPY_LOCATION srcCopyLocation(gpuRawBuffer, bufferFootprint);
    commandList->CopyTextureRegion(&dstCopyLocation, destArea.x, destArea.y, 0, &srcCopyLocation, &bufferBound);
    TransitionBufferState(texRawBuffer, D3D12_RESOURCE_STATE_COPY_DEST, destTexture->InitialState());
}

void CopyCommandEncoder::CopyTextureToBuffer(WMTexture* src, TextureArea srcArea, WMGPUBuffer* dest, size_t destOffset)
{
    Texture* srcTexture = dynamic_cast<Texture*>(src);
    GPUBuffer* destBuffer = dynamic_cast<GPUBuffer*>(dest);

    ID3D12Resource* gpuRawBuffer = destBuffer->Buffer();
    ID3D12Resource* texRawBuffer = srcTexture->Resource();

    TransitionBufferState(texRawBuffer, srcTexture->InitialState(), D3D12_RESOURCE_STATE_COPY_DEST);

    D3D12_PLACED_SUBRESOURCE_FOOTPRINT bufferFootprint;
    D3D12_RESOURCE_DESC textureDesc = texRawBuffer->GetDesc();
    bufferFootprint.Offset = 0;
    bufferFootprint.Footprint.Format = textureDesc.Format;
    bufferFootprint.Footprint.Width = srcArea.width;
    bufferFootprint.Footprint.Height = srcArea.height;
    bufferFootprint.Footprint.Depth = textureDesc.DepthOrArraySize;
    bufferFootprint.Footprint.RowPitch = AlignTextureRowPitch(srcArea.width * PixelFormatSize(srcTexture->Format()));

    D3D12_BOX textureBound;
    textureBound.top = srcArea.y;
    textureBound.bottom = srcArea.height;
    textureBound.left = srcArea.x;
    textureBound.right = srcArea.width;
    textureBound.front = 0;
    textureBound.back = 1;

    CD3DX12_TEXTURE_COPY_LOCATION dstCopyLocation(gpuRawBuffer, bufferFootprint);
    CD3DX12_TEXTURE_COPY_LOCATION srcCopyLocation(texRawBuffer, 0);
    commandList->CopyTextureRegion(&dstCopyLocation, static_cast<UINT>(destOffset), 0, 0, &srcCopyLocation, &textureBound);

    TransitionBufferState(texRawBuffer, D3D12_RESOURCE_STATE_COPY_DEST, srcTexture->InitialState());
}

void CopyCommandEncoder::EndEncoding()
{
    commandList->Close();
    commandBuffer.DynamicCast<CommandBuffer>()->AddEncodedCommandList(commandList.Get());
    commandList = nullptr;
}

void CopyCommandEncoder::TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after)
{
    if (before != after)
    {
        CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(buffer, before, after);
        commandList->ResourceBarrier(1, &barrier);
    }
}
