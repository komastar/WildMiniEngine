//
//  File:   ApplicationContext.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#ifdef _WIN32
#include <Windows.h>
#include "WMFramework.h"
#include "Application/WMApplicationContext.h"
#include "Graphics/WMGraphicsDevice.h"
#include "WMSharedPtr.h"
#include "Window/WMWindow.h"

namespace WildMini
{
    class ApplicationContext : public WMApplicationContext
    {
    public:
        virtual int ApplicationLoop() override;
        virtual void Tick() override;
    };
}
#endif // _WIN32
