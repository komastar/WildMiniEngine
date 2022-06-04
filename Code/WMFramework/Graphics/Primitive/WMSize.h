#pragma once
namespace WildMini::Graphics
{
    class WMSize
    {
    public:
        float width;
        float height;

    public:
        WMSize();
        WMSize(const WMSize& size) = default;
        WMSize(WMSize&& size) = default;
    };
}
