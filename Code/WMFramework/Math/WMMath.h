#pragma once
#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>
#include <float.h>

namespace WildMini::Math
{
    inline float DegToRad(float degree)
    {
        return static_cast<float>(degree * M_PI_2);
    }

    inline float RadToDeg(float radian)
    {
        return static_cast<float>(radian * 180.0f * M_1_PI);
    }
}
