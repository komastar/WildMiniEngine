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
#include "Graphics/Geometry/WMGeometryFactory.h"
#include "Math/WMAffineTransform2.h"
#include "Math/WMLinearTransform2.h"

using namespace WildMini;
using namespace WildMini::Graphics;
using namespace WildMini::Graphics::Primitive;
using namespace WildMini::Graphics::Geometry;
using namespace WildMini::Math;
using namespace WildMini::Object;
using namespace WildMini::Common;

struct Constants
{
    WMMatrix4 worldViewProj[3];
};

struct MainPassConstants
{
    WMVector3 eye;
    WMVector3 light;
};

EditorApplication::EditorApplication()
    : mesh(nullptr)
    , needResize(false)
{
}

EditorApplication::~EditorApplication()
{
}

void EditorApplication::OnInitialize()
{
    window = Window::WindowFactory::Create(1280, 720);
    window->Create();
    window->Show();
    window->Focus();
    window->AddResizeCallback(std::bind(&EditorApplication::OnResize, this, std::placeholders::_1, std::placeholders::_2));

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

    camera.SetView(WMVector3(0.0f, 0.0f, 15.0f), WMVector3(0.0f, 0.0f, 0.0f), WMVector3::up);
    camera.SetPerspective(0.15f * 3.1415926535f, window->GetAspect(), 1.0f, 1000.0f);

    MainPassConstants mainPass;
    mainPass.eye = camera.Position();
    mainPass.light = WMVector3(1.0f, 1.0f, 1.0f).Normalize();
    mainPassBuffer = device->CreateGPUBuffer(sizeof(MainPassConstants), WMGPUBuffer::CPUCacheMode::WRITABLE);
    mainPassBuffer->WriteData(&mainPass, sizeof(MainPassConstants));

    Constants constants;
    constants.worldViewProj[0] = (camera.ViewMatrix() * camera.ProjMatrix()).Transpose();
    constants.worldViewProj[1] = (camera.ViewMatrix() * camera.ProjMatrix()).Transpose();
    constantBuffer = device->CreateGPUBuffer(sizeof(Constants), WMGPUBuffer::CPUCacheMode::WRITABLE);
    constantBuffer->WriteData(&constants, sizeof(Constants));

    mesh = Geometry::WMGeometryFactory::MakeBox(device);

    float deltaTime = 0.0f;
    gameThread = WMThread::Create(L"Editor");
    gameThread->Initialize([&]()
        {
            auto begin = std::chrono::high_resolution_clock::now();
            Update(deltaTime);
            Render();
            auto end = std::chrono::high_resolution_clock::now();
            auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
            deltaTime = dt * 0.001f;
        });
    gameThread->Run();
}

void EditorApplication::OnTerminate()
{
    gameThread->Terminate();
}

void EditorApplication::Update(float dt)
{
    static float worldTime = 0.0f;
    worldTime += dt;
    WMAffineTransform2 at2;
    at2.Translate(0.0f, -1.0f);
    WMLinearTransform2 lt2;
    lt2.Rotate(worldTime);
    at2.Multiply(lt2);
    WMVector3 camPos = at2.v * 55.0f;
    camera.SetView(WMVector3(camPos.x, 5.0f, camPos.y), WMVector3(0.0f, 0.0f, 0.0f), WMVector3::up);

    Constants constants;
    constants.worldViewProj[0] = (camera.ViewMatrix() * camera.ProjMatrix()).Transpose();
    constants.worldViewProj[1] = (camera.ViewMatrix() * camera.ProjMatrix()).Transpose();
    constants.worldViewProj[1]._14 = 25.0f;
    constants.worldViewProj[2] = (camera.ViewMatrix() * camera.ProjMatrix()).Transpose();
    constants.worldViewProj[2]._14 = -25.0f;
    constantBuffer->WriteData(&constants, sizeof(Constants) * 3);

    MainPassConstants mainPass;
    mainPass.eye = camera.Position();
    mainPass.light = WMVector3(-1.0f, -1.0f, -1.0f).Normalize();
    mainPassBuffer->WriteData(&mainPass, sizeof(MainPassConstants));
}

void EditorApplication::Render()
{
    if (needResize)
    {
        needResize.store(false);
        swapChain->Resize(window->width, window->height);
        camera.SetPerspective(0.15f * static_cast<float>(M_PI), window->GetAspect(), 1.0f, 1000.0f);
    }

    if (WMObject<WMCommandBuffer> commandBuffer = commandQueue->CreateCommandBuffer())
    {
        if (WMObject<WMRenderCommandEncoder> renderCommandEncoder = commandBuffer->CreateRenderCommandEncoder(renderPipeline))
        {
            Primitive::WMViewport viewport = { 0, 0, window->GetWidth(), window->GetHeight(), 0.0f, 1.0f };
            renderCommandEncoder->SetViewport(viewport);
            Primitive::WMRect scissorRect = { 0, 0, window->GetWidth(), window->GetHeight() };
            renderCommandEncoder->SetScissorRect(scissorRect);
            renderCommandEncoder->ClearRenderTarget(swapChain->RenderTargetTexture(), Primitive::WMColor::black);
            renderCommandEncoder->ClearDepthStencil(swapChain->DepthStencilTexture()
                , WMRenderCommandEncoder::DepthStencilClearFlag::All
                , 0.0f
                , 0);
            renderCommandEncoder->SetRenderTargets({ swapChain->RenderTargetTexture() }, swapChain->DepthStencilTexture());
            renderCommandEncoder->SetConstantBuffer(0, constantBuffer);
            renderCommandEncoder->SetVertexBuffer(mesh->vertexBuffer, sizeof(WMVertex));
            renderCommandEncoder->DrawPrimitives(WMRenderCommandEncoder::PrimitiveType::Triangle, (uint32_t)mesh->vertices.size(), 3, 0, 0);
            renderCommandEncoder->ImguiRender();
            renderCommandEncoder->EndEncoding({ swapChain->RenderTargetTexture() });
        }
        commandBuffer->Commit();
    }

    swapChain->Present();
    commandQueue->WaitComplete();
}

void EditorApplication::OnResize(uint32_t width, uint32_t height)
{
    needResize.store(true);
}
