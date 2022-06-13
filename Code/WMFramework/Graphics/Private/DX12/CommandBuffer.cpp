#include "CommandBuffer.h"
#include "RenderCommandEncoder.h"

using namespace WildMini::Object;
using namespace WildMini::Graphics;
using namespace WildMini::Graphics::Private::DX12;

WMObject<WMRenderCommandEncoder> CommandBuffer::CreateRenderCommandEncoder(WMRenderPipeline* _renderPipeline, WMCommandList* _commandList)
{
    _commandList->Reset();
    return new RenderCommandEncoder(_renderPipeline, this, _commandList);
}

void CommandBuffer::Commit()
{
}
