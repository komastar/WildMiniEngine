//
//  File:   WMApplication.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "Application/WMApplication.h"
#include "Application/Private/ApplicationContextFactory.h"

using namespace WildMini::Application;
using namespace WildMini::Application::Private;

WMApplication::WMApplication()
    : context(nullptr)
{
    context = ApplicationContextFactory::Create();
    WMASSERT(context);
}

int WMApplication::Run()
{
    OnInitialize();
    WMASSERT(context);
    int msg = context->MessageLoop();
    OnTerminate();
    return msg;
}
