//
//  File:   EditorApplication.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Object/WMObject.h"
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

class EditorApplication : public WildMini::Application::WMApplication
{
public:
    EditorApplication();

public:
    void OnInitialize() override;
    void OnTerminate() override;

private:
    void Update(float dt);
    void Render();

private:
    WildMini::Object::WMObject<WildMini::Window::WMWindow> window;
    WildMini::Object::WMObject<WildMini::Graphics::WMGraphicsDevice> device;

    std::jthread gameLoop;
    WildMini::Object::WMObject<WildMini::Graphics::WMCommandQueue> commandQueue;
    WildMini::Object::WMObject<WildMini::Graphics::WMSwapChain> swapChain;

    WildMini::Object::WMObject<WildMini::Graphics::WMShader> vertexShader;
    WildMini::Object::WMObject<WildMini::Graphics::WMShader> pixelShader;
    WildMini::Object::WMObject<WildMini::Graphics::WMRenderPipeline> renderPipeline;

    WildMini::Object::WMObject<WildMini::Graphics::WMGPUBuffer> constantBuffer;
    WildMini::Object::WMObject<WildMini::Graphics::WMGPUBuffer> mainPassBuffer;
    WildMini::Graphics::WMCamera camera;
    WildMini::Graphics::Geometry::WMMesh* mesh;
};
