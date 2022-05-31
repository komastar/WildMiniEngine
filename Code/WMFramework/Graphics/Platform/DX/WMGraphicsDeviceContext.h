#pragma once
#ifdef _WIN32
#include "d3d12_include.h"

#include "Graphics/WMGraphicsDevice.h"
#include "Window/WMWindow.h"
#include "Graphics/Platform/DX/WMCommandListImpl.h"
#include "Graphics/Platform/DX/WMCommandQueueImpl.h"
#include "Graphics/Platform/DX/WMSwapChainImpl.h"

namespace WildMini::Graphics
{
    class WMGraphicsDeviceContext : public WMGraphicsDevice
    {
    public:
        static WMGraphicsDeviceContext* Create(WildMini::Window::WMWindow* window)
        {
            return new WMGraphicsDeviceContext(window);
        }

    private:
        WMGraphicsDeviceContext(WildMini::Window::WMWindow* window);
        virtual ~WMGraphicsDeviceContext();

    private:
        ComPtr<IDXGIFactory4> dxgiFactory;
        ComPtr<ID3D12Device> device;
        ComPtr<ID3D12CommandAllocator> commandAllocator;

        WildMini::Object::WMObject<WildMini::Window::WMWindow> window;
        WildMini::Object::WMObject<WMCommandListImpl> commandList;
        WildMini::Object::WMObject<WMCommandQueueImpl> commandQueue;
        WildMini::Object::WMObject<WMSwapChainImpl> swapChain;

    private:
        void CreateCommandQueue();
        void CreateCommandAllocator();
        void CreateCommandList();
        void CreateSwapChain();

    public:
        virtual void Create() override;
    };
}
#endif  //  _WIN32
