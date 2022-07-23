//
//  File:   WindowFactory.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "Window/Private/Win32/WindowContext.h"
#include "Window/Private/Cocoa/WindowContext.h"

namespace WildMini::Window
{
    class WindowFactory
    {
    public:
        static WMWindow* Create(uint32_t width, uint32_t height)
        {
            return new WindowContext(width, height);
        }
    };
}
