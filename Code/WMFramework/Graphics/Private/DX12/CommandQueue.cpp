//
//  File:   CommandQueue.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "CommandQueue.h"
#include "SwapChain.h"
#include "CommandBuffer.h"
#include "Window/Private/Win32/WindowContext.h"

using namespace WildMini;
using namespace WildMini::Window;
using namespace WildMini::Graphics;
using namespace WildMini::Graphics::Private::DX12;

CommandQueue::CommandQueue(GraphicsDeviceContext* _graphicsDevice
    , ID3D12CommandQueue* _commandQueue
    , ID3D12CommandAllocator* _commandAllocator
    , ID3D12GraphicsCommandList* _commandList
    , ID3D12Fence* _fence)
    : device(_graphicsDevice)
    , commandQueue(_commandQueue)
    , commandAllocator(_commandAllocator)
    , commandList(_commandList)
    , fence(_fence)
    , fenceNumber(0)
{
}

CommandQueue::~CommandQueue()
{
}

WMSharedPtr<WMCommandBuffer> CommandQueue::CreateCommandBuffer()
{
    commandAllocator->Reset();
    return new CommandBuffer(device->imguiDescHeap.Get()
        , this
        , commandAllocator.Get()
        , commandList.Get()
        , D3D12_COMMAND_LIST_TYPE_DIRECT);
}

WMSharedPtr<WMSwapChain> CommandQueue::CreateSwapChain(WMWindow* window)
{
    return new SwapChain(device, this, static_cast<WindowContext*>(window));
}

void CommandQueue::WaitComplete()
{
    commandQueue->Signal(fence.Get(), ++fenceNumber);
    if (fence->GetCompletedValue() < fenceNumber)
    {
        HANDLE eventHandle = CreateEvent(nullptr, false, false, nullptr);
        fence->SetEventOnCompletion(fenceNumber, eventHandle);
        WaitForSingleObject(eventHandle, INFINITE);
        CloseHandle(eventHandle);
    }
}

uint64_t CommandQueue::ExecuteCommandLists(uint32_t numCommandLists, ID3D12CommandList* const* commandLists)
{
    commandQueue->ExecuteCommandLists(numCommandLists, commandLists);
    commandQueue->Signal(fence.Get(), ++fenceNumber);
    return fenceNumber;
}
