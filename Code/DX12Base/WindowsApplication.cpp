#include "WindowsApplication.h"
#include "Graphics/DeviceFactory.h"

WindowsApplication::WindowsApplication(HINSTANCE hinst)
{
    instance = hinst;
}

LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

void WindowsApplication::OnInitialize()
{
    InitAppWindow();
    device = reinterpret_cast<D3D12Device*>(DeviceFactory::Create());
    device->SetWindow(hwnd);
    device->Create(width, height);
}

void WindowsApplication::InitAppWindow()
{
    WNDCLASSW wc = {};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = L"MainWnd";

    RegisterClassW(&wc);

    RECT R = { 0, 0, width, height };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
    int width = R.right - R.left;
    int height = R.bottom - R.top;

    hwnd = CreateWindowW(L"MainWnd", L"D3D App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, instance, 0);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    SetFocus(hwnd);
}

void WindowsApplication::OnTerminate()
{
}

void WindowsApplication::Run()
{
}
