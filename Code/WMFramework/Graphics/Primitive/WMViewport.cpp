//
//  File:   WMViewport.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMViewport.h"

using namespace WildMini;

WMViewport::WMViewport()
    : origin(WMPoint::zero)
    , size(WMSize::zero)
    , nearDepth(0.0f)
    , farDepth(1.0f)
{

}

WMViewport::WMViewport(float _x, float _y, float _width, float _height, float _near, float _far)
    : origin(_x, _y)
    , size(_width, _height)
    , nearDepth(_near)
    , farDepth(_far)
{

}
