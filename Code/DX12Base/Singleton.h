#pragma once
template<typename T>
class Singleton
{
protected:
    // �̱��� �ν��Ͻ� ����
    static T* instance;

    Singleton() {};
    ~Singleton() {};

public:
    // �̱��� �ν��Ͻ� ��������
    static T* GetInstance();
    // �̱��� �ν��Ͻ� �����ϱ�
    virtual void ReleaseInstance();
};

// �̱��� �ʱ�ȭ
template<typename T>
T* Singleton<T>::instance = NULL;

// �̱��� �ν��Ͻ� ��������
template<typename T>
T* Singleton<T>::GetInstance()
{
    // �̱��� �ν��Ͻ��� ���� �Ǿ� ���� �ʴٸ� ���� ����
    if (!instance)
        instance = new T;

    return instance;
}

// �̱��� �ν��Ͻ� �����ϱ�
template<typename T>
void Singleton<T>::ReleaseInstance()
{
    // �̱��� �ν��Ͻ��� �����Ǿ� �ִٸ� ���� �Ѵ�.
    if (instance)
    {
        delete instance;
        instance = NULL;
    }
}