// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#ifdef _DEBUG
#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")
#endif // _DEBUG

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")

#include <dxgi1_4.h>
#include <d3d12.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>
#include <iostream>
#include <vector>

using namespace std;

#include "SafeMacro.h"
#include "InlineMacro.h"

#include "FrameworkInterface.h"
#include "Singleton.h"

#include "CTimeManager.h"
#include "CInputManager.h"

extern HWND         g_hWnd;
extern HINSTANCE    g_hInst;

#define FPS         (60.0f)