#pragma once
#ifdef _WIN32
#include "d3d12_include.h"

#include "Graphics/IGraphicsDevice.h"
//#include "Window/IWindow.h"
#include "Graphics/Platform/DX/CommandList.h"
#include "Graphics/Platform/DX/CommandQueue.h"
#include "Graphics/Platform/DX/SwapChain.h"

namespace Core
{
    class IWindow;
    class GraphicsDeviceContext : public IGraphicsDevice
    {
    public:
        static GraphicsDeviceContext* Create(IWindow* window)
        {
            return new GraphicsDeviceContext(window);
        }

    private:
        GraphicsDeviceContext(IWindow* window);
        virtual ~GraphicsDeviceContext();

    private:
        ComPtr<IDXGIFactory4> dxgiFactory;
        ComPtr<ID3D12Device> device;
        ComPtr<ID3D12CommandAllocator> commandAllocator;

        Object<IWindow> window;
        Object<CommandList> commandList;
        Object<CommandQueue> commandQueue;
        Object<SwapChain> swapChain;

    private:
        void CreateCommandQueue();
        void CreateCommandAllocator();
        void CreateCommandList();
        void CreateSwapChain();

    public:
        virtual void Create() override;
        virtual void Update() override;
        virtual void Render() override;
    };
}
#endif  //  _WIN32
