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
#include "Log/WMLog.h"
#include "Graphics/WMImage.h"

using namespace WildMini;

struct Constants
{
    WMMatrix4 viewProj{};
};

EditorApplication::EditorApplication()
    : needResize(false)
    , window(nullptr)
    , device(nullptr)
    , commandQueue(nullptr)
    , swapChain(nullptr)
{
}

EditorApplication::~EditorApplication()
{
}

void EditorApplication::Initialize()
{
    window = WindowFactory::Create(1280, 720);
    window->Create();
    window->Show();
    window->Focus();
    window->AddResizeCallback(std::bind(&EditorApplication::OnResize, this, std::placeholders::_1, std::placeholders::_2));
    window->AddKeyboardEventHandler([&](WMKeyboardEvent keyboardEvent)
        {
            if (WMKey::RETURN == keyboardEvent.keycode)
            {
                CreateRenderPipeline();
            }
        });

    device = WMGraphicsDevice::Get();
    image = new WMImage();
    image->Create(device, L"A:\\WildMiniEngine\\Code\\Editor\\test.png");
    commandQueue = device->CreateCommandQueue();
    swapChain = commandQueue->CreateSwapChain(window);

    CreateRenderPipeline();

    camera = new WMCamera();
    camera->SetView(WMVector3::forward, WMVector3::zero, WMVector3::up);
    camera->SetOrthographics(window->width, window->height, 0.1f, 1000.0f);
    mesh = WMGeometryFactory::MakeQuad(device, 1.0f, WMColor::white);

    context->tick = [this]()
    {
        Render();
    };
}

void EditorApplication::CreateRenderPipeline()
{
    vertexShader = device->CreateShader(L"Resources/Shader/BasicShader.hlsl", "VS", WMShader::StageType::Vertex);
    pixelShader = device->CreateShader(L"Resources/Shader/BasicShader.hlsl", "PS", WMShader::StageType::Fragment);

    WMRenderPipelineDescriptor pipelineDesc = {};
    pipelineDesc.sampleCount = 1;
    pipelineDesc.vertexShader = vertexShader;
    pipelineDesc.fragmentShader = pixelShader;
    pipelineDesc.vertexDescriptor.attributes = {
        { WMVertexFormat::Float3, "POSITION",       0, 0  },
        { WMVertexFormat::Float2, "TEXCOORD",       0, 12 },
        { WMVertexFormat::Float4, "COLOR",          0, 20 },
    };

    WMRenderPipelineColorAttachmentDescriptor colorAttach;
    pipelineDesc.colorAttachments = { colorAttach };
    pipelineDesc.depthStencilPixelFormat = WMPixelFormat::DEPTH_24_UNORM_STENCIL_8;
    pipelineDesc.inputPrimitiveTopology = WMPrimitiveTopologyType::Triangle;

    renderPipeline = device->CreateRenderPipeline(pipelineDesc);
}

void EditorApplication::Terminate()
{
    progressBuffer = nullptr;
    commandQueue = nullptr;
    swapChain = nullptr;
    vertexShader = nullptr;
    pixelShader = nullptr;
    renderPipeline = nullptr;
    device = nullptr;
    window = nullptr;
}

void EditorApplication::Update(float dt)
{
}

void EditorApplication::Render()
{
    if (needResize)
    {
        needResize = false;
        swapChain->Resize(window->width, window->height);
    }

    if (WMSharedPtr<WMCommandBuffer> commandBuffer = commandQueue->CreateCommandBuffer())
    {
        if (WMSharedPtr<WMRenderCommandEncoder> renderCommandEncoder = commandBuffer->CreateRenderCommandEncoder(renderPipeline))
        {
            renderCommandEncoder->ClearRenderTarget(swapChain->RenderTargetTexture(), WMColor::cyan);
            renderCommandEncoder->ClearDepthStencil(swapChain->DepthStencilTexture()
                , WMRenderCommandEncoder::DepthStencilClearFlag::All
                , 0.0f
                , 0);
            WMViewport viewport = { 0, 0, window->GetWidth(), window->GetHeight(), 0.0f, 1.0f };
            renderCommandEncoder->SetViewport(viewport);
            WMRect scissorRect = { 0, 0, window->GetWidth(), window->GetHeight() };
            renderCommandEncoder->SetScissorRect(scissorRect);
            renderCommandEncoder->SetRenderTargets({ swapChain->RenderTargetTexture() }, swapChain->DepthStencilTexture());
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
