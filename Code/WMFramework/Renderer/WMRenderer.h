//
//  File:   WMRenderer.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include "Graphics/WMRenderCommandEncoder.h"

namespace WildMini
{
    class WMRenderer
    {
    public:
        virtual void BeginRender();
        virtual void EndRender();

        virtual void AddRenderFunction(const WMRenderCommandEncoder* encoder);

    private:

    };
}
