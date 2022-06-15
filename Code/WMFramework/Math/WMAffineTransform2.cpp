//
//  File:   WMAffineTransform2.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMAffineTransform2.h"

using namespace WildMini::Math;

WMAffineTransform2::WMAffineTransform2() : m()
{
}

WMAffineTransform2::WMAffineTransform2(const WMMatrix3& _m)
{
    m = WMMatrix2(_m);
    v = WMVector2(_m._31, _m._32);
}

WMAffineTransform2 WMAffineTransform2::Translate(float x, float y)
{
    v.x += x;
    v.y += y;

    return *this;
}

WMAffineTransform2 WMAffineTransform2::Translate(const WMVector2& _v)
{
    v.x += _v.x;
    v.y += _v.y;

    return *this;
}

WMAffineTransform2 WMAffineTransform2::Multiply(const WMAffineTransform2& at)
{
    m = m * at.m;
    v = v * at.m + at.v;

    return *this;
}

WMAffineTransform2 WMAffineTransform2::Multiply(const WMLinearTransform2& lt)
{
    m = m * lt.m;
    v = v * lt.m;

    return *this;
}

bool WMAffineTransform2::operator==(const WMAffineTransform2& at) const
{
    return m == at.m && v == at.v;
}

bool WMAffineTransform2::operator!=(const WMAffineTransform2& at) const
{
    return !(*this == at);
}
