#pragma once
#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>
#include <iostream>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix2.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "LinearTransform2.h"
#include "LinearTransform3.h"
#include "AffineTransform2.h"
#include "AffineTransform3.h"

inline float DegToRad(float degree)
{
    return static_cast<float>(degree * M_PI_2);
}

inline float RadToDeg(float radian)
{
    return static_cast<float>(radian * 180.0f * M_1_PI);
}