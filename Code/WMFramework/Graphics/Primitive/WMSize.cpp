#include "WMSize.h"

using namespace WildMini::Graphics::Primitive;

const WMSize WMSize::zero = { 0.0f, 0.0f };
const WMSize WMSize::one = { 1.0f, 1.0f };
const WMSize WMSize::negOne = { -1.0f, -1.0f };
const WMSize WMSize::inf = { FLT_MAX, FLT_MAX };
const WMSize WMSize::negInf = { FLT_MIN, FLT_MIN };

WMSize::WMSize()
    : width(0.0f)
    , height(0.0f)
{
}

WMSize::WMSize(float _width, float _height)
    : width(_width)
    , height(_height)
{
}
