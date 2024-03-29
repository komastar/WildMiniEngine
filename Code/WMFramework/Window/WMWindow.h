//
//  File:   WMWindow.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMRefCounter.h"
#include "Math/WMVector2.h"

namespace WildMini
{
    enum class WMKey
    {
        NONE = 0,
        RETURN,
        MAX
    };

    enum class WMMouseEventType
    {
        NONE = 0,
        DOWN,
        UP,
        DBL_CLICK,
        MAX
    };

    struct WMMouseEvent 
    {
        WMMouseEventType type;
        WMVector2 position;
    };

    struct WMKeyboardEvent
    {
        WMKey keycode;
    };

    class WM_API WMWindow : public WMRefCounter
    {
    public:
        WMWindow(uint32_t _width, uint32_t _height) : width(_width), height(_height) {}

    public:
        virtual void Create() = 0;
        virtual void Show() = 0;
        virtual void Hide() = 0;
        virtual void Update() = 0;
        virtual void Focus() = 0;
        virtual void SetTitle(const wchar_t* title) = 0;

        virtual void* PlatformHandle() const = 0;

        virtual float GetWidth() const = 0;
        virtual float GetHeight() const = 0;
        virtual void SetWidth(uint32_t width) = 0;
        virtual void SetHeight(uint32_t height) = 0;
        virtual void SetSize(uint32_t width, uint32_t height) = 0;
        virtual float GetAspect() const = 0;

        virtual void OnResize() = 0;
        virtual void AddResizeCallback(std::function<void(uint32_t, uint32_t)> callback) = 0;

        virtual WMWindow* AddMouseEventHandler(std::function<void(WMMouseEvent)> handler) = 0;
        virtual WMWindow* AddKeyboardEventHandler(std::function<void(WMKeyboardEvent)> handler) = 0;

    public:
        uint32_t width;
        uint32_t height;
    };
}
