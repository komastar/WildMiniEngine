#pragma once

#define TIME CTimeManager::GetInstance()

class CTimeManager : public Singleton<CTimeManager>
{
private:
    bool            m_isHardware;           //  ���� Ÿ�̸� ���� ���� Ȯ��
    float           m_fTimeScale;           //  �ð� �����
    float           m_fTimeElapsed;         //  �����Ӵ� ��� �ð�
    double          m_fFrameElapsed;
    __int64         m_nCurrTime;            //  ���� �ð�
    __int64         m_nLastTime;            //  ������ �ð�
    __int64         m_nPeriodFrequency;     //  �ð� �ֱ�

    unsigned int    m_nFrameRate;           //  FPS
    unsigned int    m_nFpsCount;            //  FPS counter
    double          m_fFpsTimeElapsed;      //  FPS ������ �ð� - ���� �ð�
    double          m_fWorldTime;           //  ��ü ��� �ð�
    double          m_fBaseElapsedTime;     //  �⺻ FPS ���� 60

public:
    CTimeManager();
    ~CTimeManager();

    bool Update(double lock);
    void Render();
    void Release();

    double GetDeltaTime() const { return m_fTimeElapsed; }
    double GetWorldTime() const { return m_fWorldTime; }
};

