#pragma once
class Application
{
public:
    virtual void OnInitialize() = 0;
    virtual void OnTerminate() = 0;
    virtual void Run() = 0;
};

