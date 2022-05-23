#include "UnitTest.h"
#include "Math/Math.h"

using namespace Core::Math;

_TEST_(Core, Math, Vector2_one)
{
    Vector2 v1 = Vector2::one;
    EXPECT_FLOAT_EQ(v1.x, 1.0f);
    EXPECT_FLOAT_EQ(v1.y, 1.0f);

    v1 *= 0.0f;
    EXPECT_FLOAT_EQ(v1.x, 0.0f);
    EXPECT_FLOAT_EQ(v1.y, 0.0f);

    v1 = Vector2::one;
    EXPECT_FLOAT_EQ(v1.x, 1.0f);
    EXPECT_FLOAT_EQ(v1.y, 1.0f);
}

_TEST_(Core, Math, Vector2_dir)
{
    Vector2 left = Vector2::left;
    EXPECT_FLOAT_EQ(left.x, -1.0f);
    EXPECT_FLOAT_EQ(left.y, 0.0f);

    Vector2 up = Vector2::up;
    EXPECT_FLOAT_EQ(up.x, 0.0f);
    EXPECT_FLOAT_EQ(up.y, 1.0f);

    Vector2 right = Vector2::right;
    EXPECT_FLOAT_EQ(right.x, 1.0f);
    EXPECT_FLOAT_EQ(right.y, 0.0f);

    Vector2 down = Vector2::down;
    EXPECT_FLOAT_EQ(down.x, 0.0f);
    EXPECT_FLOAT_EQ(down.y, -1.0f);
}