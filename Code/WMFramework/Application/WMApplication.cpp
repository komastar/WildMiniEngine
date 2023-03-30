//
//  File:   WMApplication.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "Application/WMApplication.h"
#include "Application/Private/ApplicationContextFactory.h"

using namespace WildMini;

namespace Private
{
    WMSharedPtr<WMApplication> application;
}

WMApplication::WMApplication()
    : context(nullptr)
{
    WMASSERT(!Private::application);
    Private::application = this;
    context = ApplicationContextFactory::Create();
    WMASSERT(context);
}

WMApplication::~WMApplication()
{
}

int WMApplication::Run()
{
    OnInitialize();
    WMASSERT(context);
    int msg = context->MessageLoop();
    OnTerminate();
    return msg;
}

WMSharedPtr<WMApplication> WMApplication::GlobalApp()
{
    WMASSERT(!Private::application);
    return Private::application;
}