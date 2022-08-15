//
//  File:   WMApplication.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Object/WMObject.h"
#include "WMApplicationContext.h"

namespace WildMini::Application
{
    class WM_API WMApplication : public WildMini::Object::WMRefCounter
    {
    public:
        WMApplication();
        virtual ~WMApplication();

    public:
        virtual void OnInitialize() = 0;
        virtual void OnTerminate() = 0;
        int Run();

    protected:
        WildMini::Object::WMObject<WMApplicationContext> context;
    };
}
#pragma once
