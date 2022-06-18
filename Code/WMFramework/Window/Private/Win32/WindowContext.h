//
//  File:   WindowContext.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#ifdef _WIN32
#include <Windows.h>
#include "Window/WMWindow.h"

namespace WildMini::Window
{
    class WindowContext : public WMWindow
    {
    public:
        virtual void Create() override;
        virtual void Show() override;
        virtual void Hide() override;
        virtual void* PlatformHandle() const override;
        virtual uint32_t Width() const override;
        virtual uint32_t Height() const override;
        virtual void Update() override;
        virtual void Focus() override;

    protected:
        HINSTANCE instance;
        HWND hwnd;

    private:
        const uint32_t width = 1024;
        const uint32_t height = 768;
    };
}
#endif // _WIN32
