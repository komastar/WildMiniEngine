//
//  File:   WMApplication.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "Application/WMApplication.h"
#include "Application/Private/ApplicationContextFactory.h"

using namespace WildMini;

WMApplication::WMApplication()
    : context(nullptr)
{
    context = ApplicationContextFactory::Create();
    WMASSERT(context);
}

WMApplication::~WMApplication()
{
    context = nullptr;
}

int WMApplication::Run()
{
    Initialize();
    WMASSERT(context);
    int msg = context->ApplicationLoop();
    Terminate();
    return msg;
}
