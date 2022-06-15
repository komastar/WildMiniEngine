//
//  File:   CommandQueue.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "CommandQueue.h"
#include "SwapChain.h"

using namespace WildMini::Window;
using namespace WildMini::Object;
using namespace WildMini::Graphics;
using namespace WildMini::Graphics::Private::DX12;

CommandQueue::CommandQueue(WMGraphicsDevice* _graphicsDevice, ID3D12CommandQueue* _commandQueue, ID3D12CommandAllocator* _commandAllocator, ID3D12GraphicsCommandList* _commandList, ID3D12Fence* _fence)
{

}

WMObject<WMCommandBuffer> CommandQueue::CreateCommandBuffer()
{
    return WMObject<WMCommandBuffer>();
}

WMObject<WMSwapChain> CommandQueue::CreateSwapChain(const WMWindow* window)
{
    return new SwapChain();
}

void CommandQueue::WaitComplete()
{

}

uint64_t CommandQueue::ExecuteCommandLists(uint32_t numCommandLists, ID3D12CommandList* const* commandLists)
{
    return uint64_t();
}
