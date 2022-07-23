//
//  File:   SwapChain.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "d3d12_include.h"
#include "Window/Private/Win32/WindowContext.h"
#include "Graphics/WMSwapChain.h"
#include "Graphics/WMTexture.h"

#include "GraphicsDeviceContext.h"
#include "CommandQueue.h"
#include "Texture.h"

namespace WildMini::Graphics::Private::DX12
{
    class SwapChain : public WMSwapChain
    {
    public:
        SwapChain(GraphicsDeviceContext*, CommandQueue*, Window::WindowContext*);

        enum { BUFFER_COUNT = 2 };

    public:
        virtual const WMTexture* RenderTargetTexture() const override;
        virtual const WMTexture* DepthStencilTexture() const override;
        virtual void Resize(uint32_t width, uint32_t height) override;
        virtual void Present() override;

    public:
        uint32_t Width();
        uint32_t Height();

    private:
        ComPtr<IDXGISwapChain3> swapChain;

        Object::WMObject<GraphicsDeviceContext> device;

        uint32_t width;
        uint32_t height;
        UINT swapChainIndex = 0;

        mutable Object::WMObject<Texture> renderTargets[BUFFER_COUNT];
        mutable Object::WMObject<Texture> depthStencilTexture;

        ComPtr<ID3D12DescriptorHeap> imguiDescHeap;

    private:
        void SetupRenderTargets();
        void SetupDepthStencil();
    };
}
