#include "CommandList.h"

using namespace WildMini::Graphics::Private::DX12;

CommandList::CommandList(ID3D12Device* device, ID3D12CommandAllocator* commandAllocator)
    : commandList(nullptr)
    , commandAllocator(commandAllocator)
{
    device->CreateCommandList(0
        , D3D12_COMMAND_LIST_TYPE_DIRECT
        , this->commandAllocator.Get()
        , nullptr
        , IID_PPV_ARGS(&commandList));
}

void CommandList::Close()
{
    commandList->Close();
}

void CommandList::Reset()
{
    commandList->Reset(commandAllocator.Get(), nullptr);
}
