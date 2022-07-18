//
//  File:   WMMath.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>
#include <float.h>

#include "WMVector2.h"
#include "WMVector3.h"
#include "WMVector4.h"
#include "WMVector2Int.h"
#include "WMVector3Int.h"
#include "WMVector4Int.h"
#include "WMMatrix2.h"
#include "WMMatrix3.h"
#include "WMMatrix4.h"
#include "WMAffineTransform2.h"
#include "WMAffineTransform3.h"
#include "WMLinearTransform2.h"
#include "WMLinearTransform3.h"

namespace WildMini::Math
{
    inline float DegToRad(float degree)
    {
        return static_cast<float>(degree * M_PI / 180.0f);
    }

    inline float RadToDeg(float radian)
    {
        return static_cast<float>(radian * 180.0f / M_PI);
    }
}
