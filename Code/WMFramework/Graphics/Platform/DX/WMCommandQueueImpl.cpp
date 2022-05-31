#include "Graphics/Platform/DX/WMCommandQueueImpl.h"
#include <d3d12.h>

using namespace WildMini::Graphics;

WMCommandQueueImpl::WMCommandQueueImpl(ID3D12Device* device)
    : commandQueue(nullptr)
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));
}

ID3D12CommandQueue* WMCommandQueueImpl::Get()
{
    return commandQueue.Get();
}
