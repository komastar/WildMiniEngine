//
//  File:   WMWindow.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "Object/WMRefCounter.h"

namespace WildMini::Window
{
    class WM_API WMWindow : public WildMini::Object::WMRefCounter
    {
    public:
        virtual void Create() = 0;
        virtual void Show() = 0;
        virtual void Hide() = 0;
        virtual void Update() = 0;
        virtual void Focus() = 0;

        virtual void* PlatformHandle() const = 0;

        virtual uint32_t Width() const = 0;
        virtual uint32_t Height() const = 0;
        virtual float Aspect() const = 0;
    };
}
