#pragma once
#include "Application/Application.h"
#include <Windows.h>

class EditorApplication : public Core::Application
{
public:
    EditorApplication();

public:
    virtual void OnInitialize() override;
    virtual void OnTerminate() override;
};

