#pragma once
#include <bitset>

#define INPUT CInputManager::GetInstance()
#define KEYMAX 256

class CInputManager : public Singleton<CInputManager>
{
private:
    bitset<KEYMAX>  m_bitKeyUp;
    bitset<KEYMAX>  m_bitKeyDown;

public:
    CInputManager();
    ~CInputManager();

    bool GetKeyDown(int key);
    bool GetKeyUp(int key);
    bool GetKey(int key);
    bool GetToggleKey(int key);
};

