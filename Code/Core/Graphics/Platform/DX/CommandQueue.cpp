#include "Graphics/Platform/DX/CommandQueue.h"
#include <d3d12.h>

Core::CommandQueue::CommandQueue(ID3D12Device* device)
    : commandQueue(nullptr)
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));
}

ID3D12CommandQueue* Core::CommandQueue::Get()
{
    return commandQueue.Get();
}
