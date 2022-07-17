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
#include "Graphics/Primitive/WMColor.h"
#include "Graphics/Geometry/WMVertex.h"

using namespace WildMini;
using namespace WildMini::Graphics;
using namespace WildMini::Graphics::Primitive;
using namespace WildMini::Graphics::Geometry;
using namespace WildMini::Math;
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

    vertexShader = device->CreateShader(L"Resources/Shader/BasicShader.hlsl", "VS", WMShader::StageType::Vertex);
    pixelShader = device->CreateShader(L"Resources/Shader/BasicShader.hlsl", "PS", WMShader::StageType::Fragment);

    WMRenderPipelineDescriptor pipelineDesc = {};
    pipelineDesc.sampleCount = 1;
    pipelineDesc.vertexShader = vertexShader;
    pipelineDesc.fragmentShader = pixelShader;
    pipelineDesc.vertexDescriptor.attributes = {
        { WMVertexFormat::Float3, "POSITION",   0, 0  },
        { WMVertexFormat::Float3, "NORMAL",     0, 12 },
        { WMVertexFormat::Float4, "COLOR",      0, 24 },
    };

    pipelineDesc.colorAttachments = {
        { WMPixelFormat::RGBA_8_UNML, false }
    };

    pipelineDesc.depthStencilPixelFormat = WMPixelFormat::DEPTH_24_UNORM_STENCIL_8;
    pipelineDesc.inputPrimitiveTopology = WMPrimitiveTopologyType::Triangle;

    renderPipeline = device->CreateRenderPipeline(pipelineDesc);

    camera.SetView(WMVector3::back * 5.0f, WMVector3::zero, WMVector3::up);
    camera.SetPerspective(0.3f * 3.14f
        , window->Aspect()
        , 1.0f, 1000.0f);

    struct Constants
    {
        WMMatrix4 worldViewProj;
    };

    Constants constants;
    constants.worldViewProj = camera.ViewMatrix() * camera.ProjMatrix();
    constantBuffer = device->CreateGPUBuffer(sizeof(Constants), WMGPUBuffer::CPUCacheMode::WRITABLE);
    constantBuffer->WriteData(&constants, sizeof(Constants));


    mesh = new WMMesh();
    mesh->vertices = std::vector<WMVertex>
    {
        WMVertex{WMVector3( 0.0f, 1.0f,  0.0f), WMVector3::back, WMColor::white},
        WMVertex{WMVector3( 1.0f, 0.0f,  0.0f), WMVector3::back, WMColor::white},
        WMVertex{WMVector3(-1.0f, 0.0f,  0.0f), WMVector3::back, WMColor::white}
    };

    WMObject<WMGPUBuffer> vertexBuffer;
    vertexBuffer = device->CreateGPUBuffer(mesh->vertices.size() * sizeof(WMVertex), WMGPUBuffer::CPUCacheMode::WRITABLE);
    vertexBuffer->WriteData(mesh->vertices.data(), mesh->vertices.size() * sizeof(WMVertex));
    mesh->vertexBuffer = vertexBuffer;

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
        if (WMObject<WMRenderCommandEncoder> renderCommandEncoder = commandBuffer->CreateRenderCommandEncoder(renderPipeline))
        {
            Primitive::WMViewport viewport = { 0, 0, static_cast<float>(window->Width()), static_cast<float>(window->Height()), 0.0f, 1.0f };
            renderCommandEncoder->SetViewport(viewport);
            Primitive::WMRect scissorRect = { 0, 0, static_cast<float>(window->Width()), static_cast<float>(window->Height()) };
            renderCommandEncoder->SetScissorRect(scissorRect);
            renderCommandEncoder->ClearRenderTarget(swapChain->RenderTargetTexture(), Primitive::WMColor::black);
            renderCommandEncoder->ClearDepthStencil(swapChain->DepthStencilTexture()
                , WMRenderCommandEncoder::DepthStencilClearFlag::All
                , 1.0f
                , 0);
            renderCommandEncoder->SetRenderTargets({ swapChain->RenderTargetTexture() }, swapChain->DepthStencilTexture());
            renderCommandEncoder->SetConstantBuffer(0, constantBuffer);
            renderCommandEncoder->SetVertexBuffer(mesh->vertexBuffer, sizeof(WMVertex));
            renderCommandEncoder->DrawPrimitives(WMRenderCommandEncoder::PrimitiveType::Triangle, (uint32_t)mesh->vertices.size(), 1, 0, 0);

            renderCommandEncoder->EndEncoding();
        }
        commandBuffer->Commit();
    }

    swapChain->Present();
    commandQueue->WaitComplete();
}
