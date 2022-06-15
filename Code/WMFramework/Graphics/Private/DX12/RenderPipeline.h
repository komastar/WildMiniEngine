//
//  File:   RenderPipeline.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "d3d12_include.h"
#include "Graphics/WMRenderPipeline.h"

namespace WildMini::Graphics::Private::DX12
{
    class RenderPipeline : public WMRenderPipeline
    {
    public:
        RenderPipeline(ID3D12PipelineState* pipelineState, ID3D12RootSignature* rootSignature);

    public:
        ID3D12PipelineState* PipelineState() const { return pipelineState.Get(); }
        ID3D12RootSignature* RootSignature() const { return rootSignature.Get(); }

    private:
        ComPtr<ID3D12PipelineState> pipelineState;
        ComPtr<ID3D12RootSignature> rootSignature;
    };
}
