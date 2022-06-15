//
//  File:   UnitTestVector.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "UnitTest.h"
#include "Math/WMMath.h"
#include "Math/WMVector2.h"

using namespace WildMini::Math;

_TEST_(Core, Math, Vector2_one)
{
    WMVector2 v1 = WMVector2::one;
    EXPECT_FLOAT_EQ(v1.x, 1.0f);
    EXPECT_FLOAT_EQ(v1.y, 1.0f);

    v1 *= 0.0f;
    EXPECT_FLOAT_EQ(v1.x, 0.0f);
    EXPECT_FLOAT_EQ(v1.y, 0.0f);

    v1 = WMVector2::one;
    EXPECT_FLOAT_EQ(v1.x, 1.0f);
    EXPECT_FLOAT_EQ(v1.y, 1.0f);
}

_TEST_(Core, Math, Vector2_dir)
{
    WMVector2 left = WMVector2::left;
    EXPECT_FLOAT_EQ(left.x, -1.0f);
    EXPECT_FLOAT_EQ(left.y, 0.0f);

    WMVector2 up = WMVector2::up;
    EXPECT_FLOAT_EQ(up.x, 0.0f);
    EXPECT_FLOAT_EQ(up.y, 1.0f);

    WMVector2 right = WMVector2::right;
    EXPECT_FLOAT_EQ(right.x, 1.0f);
    EXPECT_FLOAT_EQ(right.y, 0.0f);

    WMVector2 down = WMVector2::down;
    EXPECT_FLOAT_EQ(down.x, 0.0f);
    EXPECT_FLOAT_EQ(down.y, -1.0f);
}