//
//  File:   WMCommandQueue.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMSharedPtr.h"
#include "Window/WMWindow.h"
#include "Graphics/WMSwapChain.h"
#include "Graphics/WMCommandBuffer.h"

namespace WildMini
{
    class WM_API WMCommandQueue : public WMRefCounter
    {
    public:
        virtual WMSharedPtr<WMSwapChain> CreateSwapChain(WMWindow*) = 0;
        virtual WMSharedPtr<WMCommandBuffer> CreateCommandBuffer() = 0;

        virtual void WaitComplete() = 0;
    };
}
