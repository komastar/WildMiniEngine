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
        virtual void AddScene(const WMString& key, WMSharedPtr<WMScene> scene)
        {
            auto found = GetScene(key);
            if (nullptr == found)
            {
                scenes.insert({ key, scene });
            }
        }

        virtual WMSharedPtr<WMScene> GetScene(const WMString& key)
        {
            auto found = scenes.find(key);
            if (scenes.end() != found)
            {
                return found->second;
            }

            return nullptr;
        }

        virtual void RemoveScene(const WMString& key)
        {
            scenes.erase(key);
        }

    public:
        std::function<void()> tick;

    protected:
        WMSharedPtr<WMGraphicsDevice> device;
        WMSharedPtr<WMWindow> window;
        Map<WMString, WMScene*> scenes;
    };
}
