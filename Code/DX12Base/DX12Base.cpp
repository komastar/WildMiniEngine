#include "Win32Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
    Win32Application app;
    int msg = app.Run();

    return msg;
}