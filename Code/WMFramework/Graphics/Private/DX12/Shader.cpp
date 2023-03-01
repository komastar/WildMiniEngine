//
//  File:   Shader.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "Shader.h"

using namespace WildMini;

Shader::Shader(ID3DBlob* _byteCode, WMShader::StageType _stage, const std::string& _entry)
    : byteCode(_byteCode)
    , entry(_entry)
    , stage(_stage)
{
}

Shader::~Shader()
{
}

D3D12_SHADER_BYTECODE Shader::ByteCode() const
{
    return { reinterpret_cast<BYTE*>(byteCode->GetBufferPointer()), byteCode->GetBufferSize() };
}
