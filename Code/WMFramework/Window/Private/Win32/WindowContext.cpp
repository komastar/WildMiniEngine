//
//  File:   WindowContext.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#ifdef _WIN32
#include "WindowContext.h"
#include "imgui.h"

using namespace WildMini::Window;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, message, wParam, lParam))
    {
        return true;
    }

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

void WindowContext::Create()
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

    hwnd = CreateWindowW(L"MainWnd", L"WildMini Editor", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, instance, 0);
}

void WindowContext::Show()
{
    ShowWindow(hwnd, SW_SHOW);
}

void WindowContext::Hide()
{
    ShowWindow(hwnd, SW_HIDE);
}

void* WindowContext::PlatformHandle() const
{
    return hwnd;
}

uint32_t WindowContext::Width() const
{
    return width;
}

uint32_t WindowContext::Height() const
{
    return height;
}

float WindowContext::Aspect() const
{
    return static_cast<float>(width) / static_cast<float>(height);
}

void WindowContext::Update()
{
    UpdateWindow(hwnd);
}

void WindowContext::Focus()
{
    SetFocus(hwnd);
}
#endif // _WIN32
