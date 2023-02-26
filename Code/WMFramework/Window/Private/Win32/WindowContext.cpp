//
//  File:   WindowContext.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#ifdef _WIN32
#include "WindowContext.h"
//#include "imgui.h"
#include "Log/WMLog.h"

using namespace WildMini::Window;

//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WindowContext::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //if (ImGui_ImplWin32_WndProcHandler(hwnd, message, wParam, lParam))
    //{
    //    return true;
    //}

    WindowContext* window = reinterpret_cast<WindowContext*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    switch (message)
    {
    case WM_MOUSEMOVE:
    {
        auto x = (float)GET_X_LPARAM(lParam);
        auto y = (float)GET_Y_LPARAM(lParam);
        break;
    }
    case WM_LBUTTONDBLCLK:
    {
        WMLogDebug("DBL CLICK");
    }
    case WM_LBUTTONDOWN:
    {
        SetCapture(hwnd);
        auto x = (float)GET_X_LPARAM(lParam);
        auto y = (float)GET_Y_LPARAM(lParam);
        break;
    }
    case WM_RBUTTONDOWN:
    case WM_RBUTTONDBLCLK:
    {
        auto x = (float)GET_X_LPARAM(lParam);
        auto y = (float)GET_Y_LPARAM(lParam);
        break;
    }
    case WM_LBUTTONUP:
    {
        ReleaseCapture();
        break;
    }
    case WM_KEYDOWN:
    {
        WMKey keycode = WMKey::NONE;
        if (wParam == VK_RETURN)
        {
            keycode = WMKey::RETURN;
        }
        window->PostKeyboardEvent({ keycode });
        break;
    }
    case WM_SIZE:
    {
        uint32_t width = LOWORD(lParam);
        uint32_t height = HIWORD(lParam);
        window->SetSize(width, height);
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    }

    return DefWindowProcW(hwnd, message, wParam, lParam);
}

WindowContext::WindowContext(uint32_t _width, uint32_t _height)
    : WMWindow(_width, _height)
    , cacheWidth(static_cast<float>(width))
    , cacheHeight(static_cast<float>(height))
    , cacheAspect(1.0f)
    , hwnd(nullptr)
    , instance(nullptr)
{
    cacheAspect = cacheWidth / cacheWidth;
    resizeCallbackList.reserve(4);
    mouseEventHandler.reserve(4);
}

void WindowContext::Create()
{
    WNDCLASSW wc = {};
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
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
    SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)this);
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

float WindowContext::GetWidth() const
{
    return cacheWidth;
}

float WindowContext::GetHeight() const
{
    return cacheHeight;
}

void WindowContext::SetWidth(uint32_t _width)
{
    width = _width;
    cacheWidth = static_cast<float>(width);
}

void WindowContext::SetHeight(uint32_t _height)
{
    height = _height;
    cacheHeight = static_cast<float>(height);
}

float WindowContext::GetAspect() const
{
    return cacheAspect;
}

void WindowContext::OnResize()
{
    for (auto iter = resizeCallbackList.begin(); iter != resizeCallbackList.end(); ++iter)
    {
        (*iter)(width, height);
    }
}

void WindowContext::Update()
{
    UpdateWindow(hwnd);
}

void WindowContext::Focus()
{
    SetFocus(hwnd);
}
void WindowContext::SetTitle(const wchar_t* title)
{
    SetWindowTextW(hwnd, title);
}

void WindowContext::SetSize(uint32_t _width, uint32_t _height)
{
    width = _width;
    height = _height;
    cacheWidth = static_cast<float>(width);
    cacheHeight = static_cast<float>(height);
    cacheAspect = cacheWidth / cacheHeight;
    OnResize();
}

void WindowContext::AddResizeCallback(std::function<void(uint32_t, uint32_t)> callback)
{
    resizeCallbackList.push_back(callback);
}
WMWindow* WindowContext::AddMouseEventHandler(std::function<void(WMMouseEvent)> handler)
{
    mouseEventHandler.emplace_back(handler);
    return this;
}
WMWindow* WindowContext::AddKeyboardEventHandler(std::function<void(WMKeyboardEvent)> handler)
{
    keyboardEventHandler.emplace_back(handler);
    return this;
}

void WindowContext::PostMouseEvent(WMMouseEvent mouseEvent)
{
    for (auto iter = mouseEventHandler.begin(); mouseEventHandler.end() != iter; iter++)
    {
        (*iter)(mouseEvent);
    }
}

void WindowContext::PostKeyboardEvent(WMKeyboardEvent keyboardEvent)
{
    for (auto iter = keyboardEventHandler.begin(); keyboardEventHandler.end() != iter; iter++)
    {
        (*iter)(keyboardEvent);
    }
}
#endif // _WIN32
