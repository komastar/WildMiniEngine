//
//  File:   WMCommandQueue.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Object/WMObject.h"
#include "Window/WMWindow.h"
#include "Graphics/WMSwapChain.h"
#include "Graphics/WMCommandBuffer.h"

namespace WildMini::Graphics
{
    class WM_API WMCommandQueue : public Object::WMRefCounter
    {
    public:
        virtual Object::WMObject<WMSwapChain> CreateSwapChain(const Window::WMWindow*) = 0;
        virtual Object::WMObject<WMCommandBuffer> CreateCommandBuffer() = 0;

        virtual void WaitComplete() = 0;
    };
}
