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
        WMApplication();
        virtual ~WMApplication();

    public:
        virtual void OnInitialize() = 0;
        virtual void OnTerminate() = 0;
        int Run();

    protected:
        WMSharedPtr<WMApplicationContext> context;
    };
}
#pragma once
