//
//  File:   ApplicationContext.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#ifdef _WIN32
#include <Windows.h>
#include "Application/WMApplicationContext.h"
#include "Graphics/WMGraphicsDevice.h"
#include "Object/WMObject.h"
#include "Window/WMWindow.h"

namespace WildMini::Application::Private
{
    class ApplicationContext : public WMApplicationContext
    {
    public:
        virtual int MessageLoop() override;
    };
}
#endif // _WIN32
