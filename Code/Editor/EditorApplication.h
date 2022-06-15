//
//  File:   EditorApplication.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Application/WMApplication.h"
#include "Graphics/WMGraphicsDevice.h"

class EditorApplication : public WildMini::Application::WMApplication
{
public:
    EditorApplication();

public:
    void OnInitialize() override;
    void OnTerminate() override;

private:
    WildMini::Object::WMObject<WildMini::Window::WMWindow> window;
    WildMini::Object::WMObject<WildMini::Graphics::WMGraphicsDevice> device;
};
