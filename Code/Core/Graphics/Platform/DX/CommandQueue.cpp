#include "Graphics/Platform/DX/CommandQueue.h"
#include <d3d12.h>

Core::CommandQueue::CommandQueue(ID3D12CommandQueue* commandQueue)
    : commandQueue(commandQueue)
{
    
}

ID3D12CommandQueue* Core::CommandQueue::Get()
{
    return commandQueue.Get();
}
