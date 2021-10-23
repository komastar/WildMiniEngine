#pragma once
#include "CGameObject.h"
#include "CDirect3D12.h"

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
class CMainGame : public CGameObject
{
private:
    vector<IGameObject*> m_vecGameObj;
    CDirect3D12* m_pD3D12;

private:

public:
    CMainGame();
    ~CMainGame();

    // CGameObject를 통해 상속됨
    virtual BOOL Awake() override;
    virtual BOOL Start() override;
    virtual BOOL Update() override;
    virtual BOOL FixedUpdate() override;
    virtual BOOL LateUpdate() override;
    virtual BOOL Render() override;
    virtual BOOL Release() override;
};

