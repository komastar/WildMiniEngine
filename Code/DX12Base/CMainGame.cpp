#include "stdafx.h"
#include "CMainGame.h"


CMainGame::CMainGame()
{
    Awake();
}

CMainGame::~CMainGame()
{
}

BOOL CMainGame::Awake()
{
    CGameObject::Awake();
    m_pD3D12 = new CDirect3D12;
    m_vecGameObj.push_back(m_pD3D12);

    return TRUE;
}

BOOL CMainGame::Start()
{
    if (!CGameObject::Start())
    {
        return TRUE;
    }

    for (auto iter = m_vecGameObj.begin(); iter != m_vecGameObj.end(); iter++)
    {
        SAFE_START(*iter);
    }
    m_pD3D12->InitWindow();
    m_pD3D12->InitInstance(WndProc);
    if (!m_pD3D12->InitDevice())
    {
        return FALSE;
    }

    return TRUE;
}

BOOL CMainGame::Update()
{
    this->Start();
    for (auto iter = m_vecGameObj.begin(); iter != m_vecGameObj.end(); iter++)
    {
        SAFE_UPDATE(*iter);
    }

    if (INPUT->GetKeyDown(VK_ESCAPE))
    {
        PostQuitMessage(0);
    }

    return TRUE;
}

BOOL CMainGame::FixedUpdate()
{
    return TRUE;
}

BOOL CMainGame::LateUpdate()
{
    return TRUE;
}

BOOL CMainGame::Render()
{
    for (auto iter = m_vecGameObj.begin(); iter != m_vecGameObj.end(); iter++)
    {
        SAFE_RENDER(*iter);
    }

    return TRUE;
}

BOOL CMainGame::Release()
{
    CGameObject::Release();
    for (auto iter = m_vecGameObj.begin(); iter != m_vecGameObj.end(); iter++)
    {
        SAFE_RELEASE(*iter);
    }

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}