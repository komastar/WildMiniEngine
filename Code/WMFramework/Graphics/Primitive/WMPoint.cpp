#include "WMPoint.h"

using namespace WildMini::Graphics::Primitive;

const WMPoint WMPoint::zero = { 0.0f, 0.0f };
const WMPoint WMPoint::one = { 1.0f, 1.0f };
const WMPoint WMPoint::negOne = { -1.0f, -1.0f };
const WMPoint WMPoint::inf = { FLT_MAX, FLT_MAX };
const WMPoint WMPoint::negInf = { FLT_MIN, FLT_MIN };

WMPoint::WMPoint()
    : x(0.0f)
    , y(0.0f)
{
}

WMPoint::WMPoint(float _x, float _y)
    : x(_x)
    , y(_y)
{

}

WMPoint::WMPoint(const WildMini::Math::WMVector2& v)
    : x(v.x)
    , y(v.y)
{

}
