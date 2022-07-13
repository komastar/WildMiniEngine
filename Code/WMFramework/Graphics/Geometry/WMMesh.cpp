//
//  File:   WMMesh.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMMesh.h"

using namespace WildMini::Graphics::Geometry;
using namespace WildMini::Math;

WMMesh::WMMesh(std::vector<WMVector3> v)
    : vertices(v)
{
}

WMMesh::WMMesh(std::vector<WMVector3> v, std::vector<uint32_t> i)
    : vertices(v)
    , indices(i)
{
}
