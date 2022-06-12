#include "CommandBuffer.h"
#include "RenderCommandEncoder.h"

using namespace WildMini::Object;
using namespace WildMini::Graphics;
using namespace WildMini::Graphics::Private::DX12;

WMObject<WMRenderCommandEncoder> CommandBuffer::CreateRenderCommandEncoder()
{
    return new RenderCommandEncoder(nullptr);
}

void CommandBuffer::Commit()
{
}
