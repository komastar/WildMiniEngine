#include "CommandAllocator.h"

Core::CommandAllocator::CommandAllocator(ID3D12Device* device)
{
    device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
}
