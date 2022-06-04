#pragma once
namespace WildMini::Math
{
    class WMVector4Int
    {
    public:
        union
        {
            struct 
            {
                int x;
                int y;
                int z;
                int w;
            };
            int c[4];
        };

    public:
        WMVector4Int();
        WMVector4Int(const WMVector4Int& v4i) = default;
        WMVector4Int(WMVector4Int&& v4i) = default;
    };
}
