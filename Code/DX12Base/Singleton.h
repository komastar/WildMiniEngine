#pragma once
template<typename T>
class Singleton
{
protected:
    // 싱글톤 인스턴스 선언
    static T* instance;

    Singleton() {};
    ~Singleton() {};

public:
    // 싱글톤 인스턴스 가져오기
    static T* GetInstance();
    // 싱글톤 인스턴스 해제하기
    virtual void ReleaseInstance();
};

// 싱글톤 초기화
template<typename T>
T* Singleton<T>::instance = NULL;

// 싱글톤 인스턴스 가져오기
template<typename T>
T* Singleton<T>::GetInstance()
{
    // 싱글톤 인스턴스가 생성 되어 있지 않다면 새로 생성
    if (!instance)
        instance = new T;

    return instance;
}

// 싱글톤 인스턴스 해제하기
template<typename T>
void Singleton<T>::ReleaseInstance()
{
    // 싱글톤 인스턴스가 생성되어 있다면 해제 한다.
    if (instance)
    {
        delete instance;
        instance = NULL;
    }
}