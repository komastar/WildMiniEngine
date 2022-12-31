#include "WMComponentBase.h"
#include "Common/WMObject.h"

using namespace WildMini::Common;
using namespace WildMini::Component;

WMComponentBase::WMComponentBase(WMObject* _owner)
    : owner(_owner)
{
}

WMObject* WMComponentBase::GetOwner()
{
    return owner;
}
