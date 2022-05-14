#pragma once
#ifdef _WIN32
#include <Windows.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <vector>
#include <memory>
#include "Graphics/d3dx12.h"
#include "IGraphicsDevice.h"
#include "Window/IWindow.h"
#include "Math/Math.h"
#include <DirectXMath.h>

namespace Core
{
    class GraphicsDeviceContext : public Core::IGraphicsDevice
    {
        struct Vertex
        {
            DirectX::XMFLOAT3 pos;
            DirectX::XMFLOAT4 color;
        };


        struct ObjectConstants
        {
        public:
            DirectX::XMFLOAT4X4 WorldViewProj;
        };

    public:
        GraphicsDeviceContext();
        virtual ~GraphicsDeviceContext();

    private:
        ID3D12Device* device = nullptr;
        IDXGIFactory4* dxgiFactory = nullptr;
        ID3D12Fence* fence = nullptr;
        ID3D12CommandQueue* commandQueue = nullptr;
        ID3D12CommandAllocator* commandAllocator = nullptr;
        ID3D12GraphicsCommandList* commandList = nullptr;
        IDXGISwapChain* swapChain = nullptr;
        ID3D12RootSignature* rootSignature = nullptr;
        ID3D12PipelineState* pipelineState = nullptr;

        unsigned int rtvDescSize = 0;
        unsigned int dsvDescSize = 0;
        unsigned int cbvDescSize = 0;

        ID3DBlob* vsShaderByteCode;
        ID3DBlob* psShaderByteCode;

        std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;

        ID3D12Resource* swapChainBuffer[2];
        ID3D12DescriptorHeap* rtvHeap;
        ID3D12DescriptorHeap* dsvHeap;
        ID3D12DescriptorHeap* cbvHeap;

        ID3DBlob* vertexBufferCPU;
        ID3DBlob* indexBufferCPU;

        ID3D12Resource* vertexBufferGPU;
        ID3D12Resource* indexBufferGPU;

        UINT vertexSize;
        UINT indexSize;

        ID3D12Resource* vertexBufferUploader;
        ID3D12Resource* indexBufferUploader;

        ID3D12Resource* uploadBuffer;
        BYTE* mappedData = nullptr;

        D3D12_VIEWPORT viewport;
        D3D12_RECT scissorRect;

        std::vector<Vertex> vertices;
        std::vector<UINT16> indices;

        int backbufferCount;
        UINT64 currentFence = 0;

        IWindow* window;

        ID3D12Resource* depthStencilBuffer;
        DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

    public:
        virtual void Create(IWindow* window) override;
        virtual void Update() override;
        virtual void Render() override;

    private:
        ID3D12Resource* CreateDefaultBuffer(const void* initData
            , unsigned int byteSize
            , ID3D12Resource** uploadBuffer);
        void FlushCommandQueue();
        void OnResize();
    };
}
#endif  //  _WIN32
