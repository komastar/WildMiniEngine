//
//  File:   UnitTestLog.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "UnitTest.h"
#include "Log/WMLog.h"

_TEST_(System, Log, Print)
{
    WildMini::WMLogInfo("Info");
    WildMini::WMLogDebug("Debug");
    WildMini::WMLogWarning("Warning");
    WildMini::WMLogError("Error");

    WildMini::WMLogInfo(L"Info");
    WildMini::WMLogDebug(L"Debug");
    WildMini::WMLogWarning(L"Warning");
    WildMini::WMLogError(L"Error");
}
