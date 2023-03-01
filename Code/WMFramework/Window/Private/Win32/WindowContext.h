//
//  File:   WindowContext.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#ifdef _WIN32
#include <Windows.h>
#include <windowsx.h>
#include "WMFramework.h"
#include "Window/WMWindow.h"

namespace WildMini
{
    class WindowContext : public WMWindow
    {
    public:
        WindowContext(uint32_t _width, uint32_t _height);

    public:
        virtual void Create() override;
        virtual void Show() override;
        virtual void Hide() override;
        virtual void Update() override;
        virtual void Focus() override;
        virtual void SetTitle(const wchar_t* title) override;

        virtual void* PlatformHandle() const override;

        virtual float GetWidth() const override;
        virtual float GetHeight() const override;
        virtual void SetWidth(uint32_t width) override;
        virtual void SetHeight(uint32_t height) override;
        virtual void SetSize(uint32_t width, uint32_t height) override;
        virtual float GetAspect() const override;
        virtual void OnResize() override;
        virtual void AddResizeCallback(std::function<void(uint32_t, uint32_t)> callback) override;

        virtual WMWindow* AddMouseEventHandler(std::function<void(WMMouseEvent)> handler) override;
        virtual WMWindow* AddKeyboardEventHandler(std::function<void(WMKeyboardEvent)> handler) override;

    protected:
        static LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        void PostMouseEvent(WMMouseEvent);
        void PostKeyboardEvent(WMKeyboardEvent);

    protected:
        HINSTANCE instance;
        HWND hwnd;

    private:
        float cacheAspect;
        float cacheWidth;
        float cacheHeight;

        std::vector<std::function<void(uint32_t, uint32_t)>> resizeCallbackList;

        std::vector<std::function<void(WMMouseEvent)>> mouseEventHandler;
        std::vector<std::function<void(WMKeyboardEvent)>> keyboardEventHandler;
    };
}
#endif // _WIN32
