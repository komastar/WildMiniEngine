//
//  File:   RenderPipeline.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "RenderPipeline.h"

using namespace WildMini::Graphics::Private::DX12;

RenderPipeline::RenderPipeline(ID3D12PipelineState* _pipelineState, ID3D12RootSignature* _rootSignature)
    : pipelineState(_pipelineState)
    , rootSignature(_rootSignature)
{
}

RenderPipeline::~RenderPipeline()
{
}
