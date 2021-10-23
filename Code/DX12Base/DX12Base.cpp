// DX12Base.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "CMainGame.h"
#include "DX12Base.h"

// 전역 변수:
HINSTANCE   g_hInst;                                // 현재 인스턴스입니다.
HWND        g_hWnd;
CMainGame*  pMainGame;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // TODO: 여기에 코드를 입력합니다.
    g_hInst = hInstance;
    pMainGame = new CMainGame;
    pMainGame->Start();
    
    MSG msg;
    // 기본 메시지 루프입니다.
    BOOL isFrame = FALSE;
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT)
        {
            break;
        }
        else
        {
            isFrame = TIME->Update(FPS);
            pMainGame->Update();
            if(isFrame)
            {
                pMainGame->FixedUpdate();
            }
            pMainGame->LateUpdate();
            if (isFrame)
            {
                pMainGame->Render();
            }
        }
    }

    SAFE_RELEASE(pMainGame);

    return (int) msg.wParam;
}