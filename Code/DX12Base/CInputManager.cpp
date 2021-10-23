#include "stdafx.h"
#include "CInputManager.h"

CInputManager::CInputManager()
{
    for (int i = 0; i < KEYMAX; i++)
    {
        m_bitKeyUp.set(i, false);
        m_bitKeyDown.set(i, true);
    }
}


CInputManager::~CInputManager()
{
}

bool CInputManager::GetKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        if (!m_bitKeyDown[key])
        {
            m_bitKeyDown.set(key, true);

            return true;
        }
    }
    else
    {
        m_bitKeyDown.set(key, false);
    }

    return false;
}

bool CInputManager::GetKeyUp(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        m_bitKeyUp.set(key, true);
    }
    else
    {
        if (m_bitKeyUp[key])
        {
            m_bitKeyUp.set(key, false);
            return true;
        }
    }

    return false;
}

bool CInputManager::GetKey(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        return true;
    }

    return false;
}

bool CInputManager::GetToggleKey(int key)
{
    if (GetKeyState(key) & 0x0001)
    {
        return true;
    }

    return false;
}
