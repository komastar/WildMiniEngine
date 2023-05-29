//
//  File:   WMApplication.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMSharedPtr.h"
#include "WMApplicationContext.h"

namespace WildMini
{
    class WM_API WMApplication : public WMRefCounter
    {
    public:
        static WMSharedPtr<WMApplication> GlobalApp();

    public:
        WMApplication();
        virtual ~WMApplication();

    public:
        virtual void Initialize() = 0;
        virtual void Terminate() = 0;
        int Run();

    protected:
        WMSharedPtr<WMApplicationContext> context;
    };
}
#pragma once
