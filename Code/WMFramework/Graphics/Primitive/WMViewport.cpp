#include "WMViewport.h"

using namespace WildMini::Graphics::Primitive;

WMViewport::WMViewport()
    : origin(WMPoint::zero)
    , size(WMSize::zero)
    , near(0.0f)
    , far(1.0f)
{

}

WMViewport::WMViewport(float _x, float _y, float _width, float _height, float _near, float _far)
    : origin(_x, _y)
    , size(_width, _height)
    , near(_near)
    , far(_far)
{

}
