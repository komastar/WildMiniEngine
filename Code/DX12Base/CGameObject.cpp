#include "stdafx.h"
#include "CGameObject.h"


CGameObject::CGameObject()
{
    Awake();
}

CGameObject::~CGameObject()
{
}

BOOL CGameObject::Awake()
{
    return TRUE;
}

BOOL CGameObject::Start()
{
    if (isStart == FALSE)
    {
        isStart = TRUE;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CGameObject::Update()
{
    Start();

    return TRUE;
}

BOOL CGameObject::FixedUpdate()
{
    return TRUE;
}

BOOL CGameObject::LateUpdate()
{
    return TRUE;
}

BOOL CGameObject::Render()
{
    if (isRender)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CGameObject::Release()
{
    return TRUE;
}
