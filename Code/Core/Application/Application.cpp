#include "Application.h"

int Core::IApplication::Run()
{
    OnInitialize();
    int msg = MessageLoop();
    OnTerminate();

    return msg;
}
