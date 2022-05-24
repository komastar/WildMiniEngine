#include "Graphics/Platform/DX/CommandList.h"

Core::CommandList::CommandList(ID3D12Device* device, ID3D12CommandAllocator* commandAllocator)
    : commandList(nullptr)
    , commandAllocator(commandAllocator)
{
    device->CreateCommandList(0
        , D3D12_COMMAND_LIST_TYPE_DIRECT
        , this->commandAllocator.Get()
        , nullptr
        , IID_PPV_ARGS(&commandList));
}

void Core::CommandList::Close()
{
    commandList->Close();
}

void Core::CommandList::Reset()
{
    commandList->Reset(commandAllocator.Get(), nullptr);
}
