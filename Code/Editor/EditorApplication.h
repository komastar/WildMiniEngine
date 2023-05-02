//
//  File:   EditorApplication.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMSharedPtr.h"
#include "Application/WMApplication.h"
#include "Window/WMWindow.h"

namespace WildMini
{
    class EditorApplication : public WMApplication
    {
    public:
        EditorApplication();
        virtual ~EditorApplication();

    public:
        void OnInitialize() override;
        void CreateRenderPipeline();
        void OnTerminate() override;

    private:
        void Update(float dt);
        void Render();

    private:
        WMSharedPtr<WMWindow> window;
    };
}
