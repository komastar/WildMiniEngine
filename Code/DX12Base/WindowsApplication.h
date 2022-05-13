#pragma once
#include "Application/Application.h"
#include "Graphics/D3D12Device.h"
#include <Windows.h>

class WindowsApplication : public Application
{
private:
    HINSTANCE instance;
    HWND hwnd;

    D3D12Device* device;

private:
    const int width = 1024;
    const int height = 768;

public:
    WindowsApplication(HINSTANCE hinst);

public:
    virtual void OnInitialize() override;
    virtual void OnTerminate() override;
    virtual void Run() override;

private:
    void InitAppWindow();
};

