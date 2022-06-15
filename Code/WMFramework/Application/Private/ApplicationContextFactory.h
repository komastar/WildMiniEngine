//
//  File:   ApplicationContextFactory.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "Application/WMApplication.h"
#include "Win32/ApplicationContext.h"
#include "Cocoa/ApplicationContext.h"
#include "Window/WMWindow.h"
#include "Graphics/WMGraphicsDevice.h"

namespace WildMini::Application::Private
{
    class ApplicationContextFactory
    {
    public:
        static WMApplicationContext* Create()
        {
            return new ApplicationContext();
        }
    };
}
