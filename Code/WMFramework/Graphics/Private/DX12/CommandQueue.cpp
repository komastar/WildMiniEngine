#include "CommandQueue.h"

using namespace WildMini::Graphics::Private::DX12;

CommandQueue::CommandQueue(ID3D12Device* device)
    : commandQueue(nullptr)
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));
}

ID3D12CommandQueue* CommandQueue::Get()
{
    return commandQueue.Get();
}
