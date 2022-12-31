//
//  File:   d3d12_include.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include <Windows.h>

#include <dxgi1_4.h>
#include <d3d12.h>
#include <d3dcompiler.h>

#include "d3dx12.h"

#include "WMSharedPtr.h"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Microsoft::WRL;

constexpr inline uint32_t AlignTextureRowPitch(size_t size)
{
    constexpr uint32_t alignmentSize = D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - 1;

    return (size + alignmentSize) & ~alignmentSize;
}

constexpr inline uint32_t AlignGPUBufferSize(size_t size)
{
    constexpr uint32_t alignSize = D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT - 1;
    return (size + alignSize) & ~alignSize;
}
