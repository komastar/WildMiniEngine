#pragma once
#include "WMVector2.h"
#include "WMMatrix2.h"
#include "WMLinearTransform2.h"

namespace WildMini::Math
{
    class WMMatrix2;
    class WMVector2;
    class WMLinearTransform2;
    class WMAffineTransform2
    {
    public:
        WMMatrix2 m;
        WMVector2 v;

    public:
        WMAffineTransform2();
        WMAffineTransform2(const class WMMatrix3& _m);

    public:
        WMAffineTransform2 Translate(float x, float y);
        WMAffineTransform2 Translate(const WMVector2& _v);
        WMAffineTransform2 Multiply(const WMAffineTransform2& at);
        WMAffineTransform2 Multiply(const WMLinearTransform2& lt);

    public:
        bool operator==(const WMAffineTransform2& at) const;
        bool operator!=(const WMAffineTransform2& at) const;
    };
}
