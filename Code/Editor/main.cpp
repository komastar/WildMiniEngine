//
//  File:   main.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "EditorApplication.h"

#ifdef _DEBUG
#include "dxgidebug.h"
#endif // _DEBUG
#include <wrl/client.h>
#include "Log/WMLog.h"

using namespace WildMini;

int main(int argc, char** argv)
{
    EditorApplication app;
    int msg = app.Run();

#ifdef _DEBUG
    Microsoft::WRL::ComPtr<IDXGIDebug> debug;
    HMODULE dxgiDebugDll = GetModuleHandleW(L"dxgidebug.dll");
    if (nullptr == dxgiDebugDll)
    {
        LogDebug("GetModuleHandle failed : dxgidebug.dll");
        return -1;
    }

    decltype(&DXGIGetDebugInterface) GetDebugInterface = reinterpret_cast<decltype(&DXGIGetDebugInterface)>(GetProcAddress(dxgiDebugDll, "DXGIGetDebugInterface"));
    if (nullptr == GetDebugInterface)
    {
        LogDebug("GetProcAddress failed : DXGIGetDebugInterface");
        return -1;
    }

    GetDebugInterface(IID_PPV_ARGS(&debug));
    debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_DETAIL);
    debug = nullptr;
#endif // _DEBUG

    return msg;
}
