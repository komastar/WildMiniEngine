//
//  File:   WMApplicationContext.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMSharedPtr.h"
#include "Window/WMWindow.h"
#include "Graphics/WMGraphicsDevice.h"
#include "Scene/WMScene.h"

namespace WildMini
{
    class WM_API WMApplicationContext : public WMRefCounter
    {
    public:
        virtual int ApplicationLoop() = 0;
        virtual void Tick() = 0;

    protected:
        WMGraphicsDevice* device;
        WMWindow* window;
        Vector<WMScene*> scenes;
    };
}
