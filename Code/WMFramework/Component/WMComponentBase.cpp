#include "WMComponentBase.h"
#include "Common/WMObject.h"

using namespace WildMini;

WMComponentBase::WMComponentBase(WMObject* _owner)
    : owner(_owner)
{
}

WMObject* WMComponentBase::GetOwner()
{
    return owner;
}
