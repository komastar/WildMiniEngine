#pragma once
#include "d3d12_include.h"
#include "Object/WMObject.h"
#include "Graphics/WMRenderCommandEncoder.h"
#include "Graphics/Private/DX12/CommandList.h"

namespace WildMini::Graphics::Private::DX12
{
    class RenderCommandEncoder : public WMRenderCommandEncoder
    {
    public:
        RenderCommandEncoder(WMCommandList* _commandList);

    public:
        virtual void SetViewport(const Primitive::WMViewport& viewport) override;
        virtual void SetScissorRect(const Primitive::WMRect& rect) override;
        virtual void SetRenderTarget(const WMTexture* renderTarget) override;
        virtual void ClearRenderTarget(const WMTexture* renderTarget, const Primitive::WMColor& color) override;


    protected:
        Object::WMObject<WMCommandList> commandList;
    };
}
