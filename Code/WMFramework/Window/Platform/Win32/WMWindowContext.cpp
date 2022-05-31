#ifdef _WIN32
#include "WMWindowContext.h"

using namespace WildMini::Window;

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

void WMWindowContext::Create()
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

    RECT R = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
    int width = R.right - R.left;
    int height = R.bottom - R.top;

    hwnd = CreateWindowW(L"MainWnd", L"D3D App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, instance, 0);
}

void WMWindowContext::Show()
{
    ShowWindow(hwnd, SW_SHOW);
}

void WMWindowContext::Hide()
{
    ShowWindow(hwnd, SW_HIDE);
}

void* WMWindowContext::PlatformHandle()
{
    return hwnd;
}

uint32_t WMWindowContext::Width()
{
    return width;
}

uint32_t WMWindowContext::Height()
{
    return height;
}

void WMWindowContext::Update()
{
    UpdateWindow(hwnd);
}

void WMWindowContext::Focus()
{
    SetFocus(hwnd);
}
#endif // _WIN32
