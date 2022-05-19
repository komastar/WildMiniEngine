#pragma once
#include <Windows.h>

#include <dxgi1_4.h>
#include <d3d12.h>
#include <d3dcompiler.h>

#include "d3dx12.h"

#include "Common/Object.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Microsoft::WRL;