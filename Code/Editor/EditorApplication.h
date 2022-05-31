#pragma once
#include "Application/WMApplication.h"
#include <Windows.h>

class EditorApplication : public WildMini::Application::WMApplication
{
public:
    EditorApplication();

public:
    void OnInitialize() override;
    void OnTerminate() override;
};
