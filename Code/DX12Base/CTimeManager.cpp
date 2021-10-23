#include "stdafx.h"
#include "CTimeManager.h"


CTimeManager::CTimeManager() :
    m_fBaseElapsedTime(1.0f / 60.0f),
    m_nFrameRate(0),
    m_nFpsCount(0),
    m_fFpsTimeElapsed(0.0f),
    m_fFrameElapsed(0.0f),
    m_fWorldTime(0.0f),
    m_nPeriodFrequency(0),
    m_nCurrTime(0),
    m_nLastTime(0),
    m_fTimeElapsed(0.0f)
{
    //  고성능 타이머 지원 여부 체크
    if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_nPeriodFrequency))
    {
        m_isHardware = true;
        QueryPerformanceCounter((LARGE_INTEGER*)&m_nLastTime);

        m_fTimeScale = 1.0f / m_nPeriodFrequency;
    }
    else
    {
        m_isHardware = false;
        m_nLastTime = timeGetTime();
        m_fTimeScale = 0.001000f;           //  FIXED VALUE 1ms
    }
}


CTimeManager::~CTimeManager()
{
}

bool CTimeManager::Update(double lockFps)
{
    bool isFixedUpdate = false;

    if (m_isHardware)
    {
        QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurrTime);
    }
    else
    {
        m_nCurrTime = timeGetTime();
    }

    //  DELTA TIME
    m_fTimeElapsed = (m_nCurrTime - m_nLastTime) * m_fTimeScale;
    m_fFrameElapsed += m_fTimeElapsed;
    m_fFpsTimeElapsed += m_fTimeElapsed;
    m_fWorldTime += m_fTimeElapsed;
    m_nLastTime = m_nCurrTime;

    if (lockFps > 0.0f)
    {
        if (m_fFrameElapsed > (1.0 / lockFps))
        {
            isFixedUpdate = true;
        }
    }
    else
    {
        if (m_fFrameElapsed >= m_fBaseElapsedTime)
        {
            isFixedUpdate = true;
        }
    }

    if (isFixedUpdate)
    {
        m_nFpsCount++;
        m_fFrameElapsed = 0.0f;
    }

    if (m_fFpsTimeElapsed >= 1.0f)
    {
        m_nFrameRate = m_nFpsCount;
        m_nFpsCount = 0;
        m_fFpsTimeElapsed = 0.0f;
    }

    return isFixedUpdate;
}

void CTimeManager::Render()
{
}

void CTimeManager::Release()
{
}
