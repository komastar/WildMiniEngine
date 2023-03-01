//
//  File:   UnitTestColor.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "UnitTest.h"
#include "Graphics/Primitive/WMColor.h"

using namespace WildMini;

_TEST_(Core, Graphics, Color)
{
    WMColor c;
    EXPECT_FLOAT_EQ(c.r, 0.0f);
    EXPECT_FLOAT_EQ(c.g, 0.0f);
    EXPECT_FLOAT_EQ(c.b, 0.0f);
    EXPECT_FLOAT_EQ(c.a, 0.0f);
}
