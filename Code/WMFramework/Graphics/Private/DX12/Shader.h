//
//  File:   Shader.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "d3d12_include.h"
#include "Graphics/WMShader.h"

namespace WildMini::Graphics::Private::DX12
{
    class Shader : public WildMini::Graphics::WMShader
    {
    public:
        Shader(ID3DBlob* _byteCode, WMShader::StageType _stage, const std::string& _entry);
        virtual ~Shader();

        D3D12_SHADER_BYTECODE ByteCode() const;

    private:
        WMShader::StageType stage;
        std::string entry;
        ComPtr<ID3DBlob> byteCode;
    };
}
