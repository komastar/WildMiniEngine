#include "RenderPipeline.h"

using namespace WildMini::Graphics::Private::DX12;

RenderPipeline::RenderPipeline(ID3D12PipelineState* _pipelineState, ID3D12RootSignature* _rootSignature)
    : pipelineState(_pipelineState)
    , rootSignature(_rootSignature)
{
}
