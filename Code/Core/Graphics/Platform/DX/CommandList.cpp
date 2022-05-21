#include "Graphics/Platform/DX/CommandList.h"

Core::CommandList::CommandList(ID3D12GraphicsCommandList* commandList, ID3D12CommandAllocator* commandAllocator)
    : commandList(commandList)
    , commandAllocator(commandAllocator)
{
}

void Core::CommandList::Close()
{
    commandList->Close();
}

void Core::CommandList::Reset()
{
    commandList->Reset(commandAllocator.Get(), nullptr);
}
