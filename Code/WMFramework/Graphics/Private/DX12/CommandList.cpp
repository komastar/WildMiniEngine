#include "CommandList.h"
#include "Texture.h"

using namespace WildMini::Graphics::Private::DX12;
using namespace WildMini::Graphics::Primitive;

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

void CommandList::SetViewport(const WMViewport& viewport)
{
    D3D12_VIEWPORT vp = {
        viewport.x, viewport.y,
        viewport.width, viewport.height,
        viewport.nearDepth, viewport.farDepth
    };
    commandList->RSSetViewports(1, &vp);
}

void CommandList::SetScissorRect(const WMRect& rect)
{
    D3D12_RECT scissorRect = {
        static_cast<LONG>(rect.x),
        static_cast<LONG>(rect.y),
        static_cast<LONG>(rect.x + rect.width),
        static_cast<LONG>(rect.y + rect.height)
    };
    commandList->RSSetScissorRects(1, &scissorRect);
}

void CommandList::SetRenderTarget(const Graphics::WMTexture* renderTarget)
{
    D3D12_CPU_DESCRIPTOR_HANDLE renderTargetHandle = dynamic_cast<const Texture*>(renderTarget)->renderTargetView;
    commandList->OMSetRenderTargets(1, &renderTargetHandle, false, nullptr);
}

void CommandList::Close()
{
    commandList->Close();
}

void CommandList::Reset()
{
    commandList->Reset(commandAllocator.Get(), nullptr);
}

void CommandList::ClearRenderTarget(const Graphics::WMTexture* renderTarget, const Primitive::WMColor& color)
{
    D3D12_CPU_DESCRIPTOR_HANDLE renderTargetHandle = dynamic_cast<const Texture*>(renderTarget)->renderTargetView;
    commandList->ClearRenderTargetView(renderTargetHandle, color.c, 0, nullptr);
}
