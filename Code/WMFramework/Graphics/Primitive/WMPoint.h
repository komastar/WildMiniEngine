#pragma once
namespace WildMini::Graphics
{
    class WMPoint
    {
    public:
        float x;
        float y;

    public:
        WMPoint();
        WMPoint(const WMPoint& point) = default;
        WMPoint(WMPoint&& point) = default;
    };
}
