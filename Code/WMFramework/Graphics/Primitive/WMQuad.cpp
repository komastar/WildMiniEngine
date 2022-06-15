//
//  File:   WMQuad.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMQuad.h"

using namespace WildMini::Math;
using namespace WildMini::Graphics::Primitive;

const WMQuad WMQuad::zero = { Vector2::zero, Vector2::zero, Vector2::zero, Vector2::zero };
const WMQuad WMQuad::one = { Vector2::zero, Vector2::right, Vector2::up, Vector2::one };
const WMQuad WMQuad::inf = { Vector2::zero, Vector2::infRight, Vector2::infUp, Vector2::inf };

WMQuad::WMQuad()
    : lt(Vector2::zero)
    , rt(Vector2::zero)
    , lb(Vector2::zero)
    , rb(Vector2::zero)
{
}

WMQuad::WMQuad(Vector2 _lt, Vector2 _rt, Vector2 _lb, Vector2 _rb)
    : lt(_lt)
    , rt(_rt)
    , lb(_lb)
    , rb(_rb)
{
}
