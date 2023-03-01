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
#include "Graphics/WMGraphicsDevice.h"
#include "Graphics/WMCommandQueue.h"
#include "Graphics/WMSwapChain.h"
#include "Graphics/WMGPUBuffer.h"
#include "Graphics/WMShader.h"
#include "Graphics/WMRenderPipeline.h"
#include "Graphics/WMCamera.h"
#include "Graphics/Geometry/WMMesh.h"
#include "Common/WMThread.h"

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

        void OnResize(uint32_t width, uint32_t height);

    private:
        WMSharedPtr<WMWindow> window;
        WMSharedPtr<WMGraphicsDevice> device;

        WMSharedPtr<WMThread> gameThread;
        WMSharedPtr<WMCommandQueue> commandQueue;
        WMSharedPtr<WMSwapChain> swapChain;

        WMSharedPtr<WMShader> vertexShader;
        WMSharedPtr<WMShader> pixelShader;
        WMSharedPtr<WMRenderPipeline> renderPipeline;

        WMSharedPtr<WMGPUBuffer> progressBuffer;
        WMCamera uiCamera;
        WMMesh* uiMesh;

        std::atomic_bool needResize;
        std::atomic_bool needShaderCompile;
    };
}
