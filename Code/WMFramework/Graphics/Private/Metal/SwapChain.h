//
//  SwapChain.h
//  WMFramework
//
//  Created by Eugene Kim on 2023/04/29.
//

#ifdef __APPLE__
#ifndef SwapChain_h
#define SwapChain_h
#include "Graphics/WMSwapChain.h"
#include "Graphics/WMTexture.h"

#include "Graphics/Private/Metal/CommandQueue.h"
#include "Window/WMWindow.h"

namespace WildMini
{
    class SwapChain : public WMSwapChain
    {
    public:
        SwapChain(CommandQueue*, WMWindow*);
        ~SwapChain();

    public:
        const WMTexture *RenderTargetTexture() const override;
        const WMTexture *DepthStencilTexture() const override;
        void Resize(uint32_t width, uint32_t height) override;
        void Present() override;
    };
}
#endif /* SwapChain_h */
#endif /* __APPLE__ */
