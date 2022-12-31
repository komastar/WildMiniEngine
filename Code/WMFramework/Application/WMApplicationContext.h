//
//  File:   WMApplicationContext.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMSharedPtr.h"
#include "Window/WMWindow.h"
#include "Graphics/WMGraphicsDevice.h"

namespace WildMini::Application
{
    class WM_API WMApplicationContext : public WildMini::WMRefCounter
    {
    public:
        virtual int MessageLoop() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;

    protected:
        WildMini::Graphics::WMGraphicsDevice* device;
        WildMini::Window::WMWindow* window;
    };
}
