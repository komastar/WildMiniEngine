#include "Application/WMApplication.h"

using namespace WildMini::Application;

WMApplication::WMApplication()
    : context(nullptr)
    , device(nullptr)
    , window(nullptr)
{
}

int WMApplication::Run()
{
    OnInitialize();
    int msg = context->MessageLoop();
    OnTerminate();
    return msg;
}
