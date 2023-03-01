//
//  File:   WMRect.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMRect.h"

using namespace WildMini;

const WMRect WMRect::zero = { WMPoint::zero, WMSize::zero };
const WMRect WMRect::one = { WMPoint::zero, WMSize::one };
const WMRect WMRect::inf = { WMPoint::zero, WMSize::inf };

WMRect::WMRect()
    : origin(WMPoint::zero)
    , size(WMSize::zero)
{
}

WMRect::WMRect(float _x, float _y, float _width, float _height)
    : origin(_x, _y)
    , size(_width, _height)
{
}

WMRect::WMRect(const WMPoint& _origin, const WMSize& _size)
{
}
