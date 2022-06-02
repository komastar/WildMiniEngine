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
