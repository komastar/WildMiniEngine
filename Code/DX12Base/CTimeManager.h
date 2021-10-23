#pragma once

#define TIME CTimeManager::GetInstance()

class CTimeManager : public Singleton<CTimeManager>
{
private:
    bool            m_isHardware;           //  고성능 타이머 지원 여부 확인
    float           m_fTimeScale;           //  시간 경과량
    float           m_fTimeElapsed;         //  프레임당 경과 시간
    double          m_fFrameElapsed;
    __int64         m_nCurrTime;            //  현재 시간
    __int64         m_nLastTime;            //  마지막 시간
    __int64         m_nPeriodFrequency;     //  시간 주기

    unsigned int    m_nFrameRate;           //  FPS
    unsigned int    m_nFpsCount;            //  FPS counter
    double          m_fFpsTimeElapsed;      //  FPS 마지막 시간 - 현재 시간
    double          m_fWorldTime;           //  전체 경과 시간
    double          m_fBaseElapsedTime;     //  기본 FPS 제한 60

public:
    CTimeManager();
    ~CTimeManager();

    bool Update(double lock);
    void Render();
    void Release();

    double GetDeltaTime() const { return m_fTimeElapsed; }
    double GetWorldTime() const { return m_fWorldTime; }
};

