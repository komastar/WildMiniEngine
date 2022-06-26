//
//  File:   EditorApplication.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "EditorApplication.h"
#include "Application/Private/ApplicationContextFactory.h"
#include "Window/Private/WindowFactory.h"
#include "Graphics/Private/GraphicsDeviceFactory.h"

using namespace WildMini;
using namespace WildMini::Graphics;
using namespace WildMini::Object;

EditorApplication::EditorApplication()
{
}

void EditorApplication::OnInitialize()
{
    window = Window::WindowFactory::Create();
    window->Create();
    window->Show();
    window->Focus();

    device = Graphics::Private::GraphicsDeviceFactory::Create();
    commandQueue = device->CreateCommandQueue();
    swapChain = commandQueue->CreateSwapChain(window);

    vertexBuffer = device->CreateGPUBuffer(50000, WMGPUBuffer::CPUCacheMode::WRITABLE);

    vertexShader = device->CreateShader(L"Resources/Shader/BasicShader.hlsl", "VS", WMShader::StageType::Vertex);
    pixelShader = device->CreateShader(L"Resources/Shader/BasicShader.hlsl", "PS", WMShader::StageType::Fragment);

    WMRenderPipelineDescriptor pipelineDesc = {};
    pipelineDesc.sampleCount = 1;
    pipelineDesc.vertexShader = vertexShader;
    pipelineDesc.fragmentShader = pixelShader;
    pipelineDesc.vertexDescriptor.attributes = {
        { WMVertexFormat::Float3, "POSITION",   0, 0 },
        { WMVertexFormat::Float3, "NORMAL",     0, 0 },
        { WMVertexFormat::Float4, "COLOR",      0, 0 },
    };

    pipelineDesc.colorAttachments = {
        { WMPixelFormat::RGBA_8_UNML, false }
    };

    pipelineDesc.depthStencilPixelFormat = WMPixelFormat::DEPTH_24_UNORM_STENCIL_8;
    pipelineDesc.inputPrimitiveTopology = WMPrimitiveTopologyType::Triangle;

    renderPipeline = device->CreateRenderPipeline(pipelineDesc);

    gameLoop = std::jthread([&](std::stop_token token)
        {
            while (!token.stop_requested())
            {
                Update(0.0f);
                Render();
            }
        });
}

void EditorApplication::OnTerminate()
{
    gameLoop.request_stop();
    gameLoop.join();
}

void EditorApplication::Update(float dt)
{
}

void EditorApplication::Render()
{
    if (WMObject<WMCommandBuffer> commandBuffer = commandQueue->CreateCommandBuffer())
    {
        if (WMObject<WMRenderCommandEncoder> renderCommandEncoder = commandBuffer->CreateRenderCommandEncoder())
        {
            Primitive::WMViewport viewport = { 0, 0, static_cast<float>(window->Width()), static_cast<float>(window->Height()), 0.0f, 1.0f };
            renderCommandEncoder->SetViewport(viewport);
            Primitive::WMRect scissorRect = { 0, 0, static_cast<float>(window->Width()), static_cast<float>(window->Height()) };
            renderCommandEncoder->SetScissorRect(scissorRect);
            renderCommandEncoder->ClearRenderTarget(swapChain->RenderTargetTexture(), Primitive::WMColor::red);
            renderCommandEncoder->ClearDepthStencil(swapChain->DepthStencilTexture()
                , WMRenderCommandEncoder::DepthStencilClearFlag::All
                , 1.0f
                , 0);
            renderCommandEncoder->SetRenderTargets({ swapChain->RenderTargetTexture() }, swapChain->DepthStencilTexture());
            renderCommandEncoder->EndEncoding();
        }
        commandBuffer->Commit();
    }

    swapChain->Present();
    commandQueue->WaitComplete();
}
