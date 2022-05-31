#include "WMCommandListImpl.h"

using namespace WildMini::Graphics;

WMCommandListImpl::WMCommandListImpl(ID3D12Device* device, ID3D12CommandAllocator* commandAllocator)
    : commandList(nullptr)
    , commandAllocator(commandAllocator)
{
    device->CreateCommandList(0
        , D3D12_COMMAND_LIST_TYPE_DIRECT
        , this->commandAllocator.Get()
        , nullptr
        , IID_PPV_ARGS(&commandList));
}

void WMCommandListImpl::Close()
{
    commandList->Close();
}

void WMCommandListImpl::Reset()
{
    commandList->Reset(commandAllocator.Get(), nullptr);
}
