//
//  File:   WMMesh.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Math/WMVector3.h"

namespace WildMini::Graphics::Geometry
{
    class WMMesh
    {
    public:
        WMMesh() = default;
        WMMesh(std::vector<WildMini::Math::WMVector3> v);
        WMMesh(std::vector<WildMini::Math::WMVector3> v, std::vector<uint32_t> i);

    public:
        std::vector<WildMini::Math::WMVector3> vertices;
        std::vector<uint32_t> indices;
    };
}
