#pragma once
#include "Object/WMRefCounter.h"
#include "Graphics/WMRenderCommandEncoder.h"
#include "WMRenderPipeline.h"
#include "WMCommandList.h"

namespace WildMini::Graphics
{
    class WMCommandBuffer : public Object::WMRefCounter
    {
    public:
        virtual Object::WMObject<WMRenderCommandEncoder> CreateRenderCommandEncoder(WMRenderPipeline* _renderPipeline, WMCommandList* _commandList) = 0;
        virtual void Commit() = 0;
    };
}
