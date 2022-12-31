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

class EditorApplication : public WildMini::Application::WMApplication
{
public:
    EditorApplication();
    virtual ~EditorApplication();

public:
    void OnInitialize() override;
    void OnTerminate() override;

private:
    void Update(float dt);
    void Render();

    void OnResize(uint32_t width, uint32_t height);

private:
    WildMini::WMSharedPtr<WildMini::Window::WMWindow> window;
    WildMini::WMSharedPtr<WildMini::Graphics::WMGraphicsDevice> device;

    WildMini::WMSharedPtr<WildMini::Common::WMThread> gameThread;
    WildMini::WMSharedPtr<WildMini::Graphics::WMCommandQueue> commandQueue;
    WildMini::WMSharedPtr<WildMini::Graphics::WMSwapChain> swapChain;

    WildMini::WMSharedPtr<WildMini::Graphics::WMShader> vertexShader;
    WildMini::WMSharedPtr<WildMini::Graphics::WMShader> pixelShader;
    WildMini::WMSharedPtr<WildMini::Graphics::WMRenderPipeline> renderPipeline;

    WildMini::WMSharedPtr<WildMini::Graphics::WMGPUBuffer> progressBuffer;
    WildMini::WMSharedPtr<WildMini::Graphics::WMGPUBuffer> progressBuffer2;
    WildMini::Graphics::WMCamera uiCamera;
    WildMini::Graphics::Geometry::WMMesh* uiMesh;

    std::atomic_bool needResize;
};
