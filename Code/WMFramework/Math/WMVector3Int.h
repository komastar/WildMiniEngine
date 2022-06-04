#pragma once
namespace WildMini::Math
{
    class WMVector3Int
    {
    public:
        union
        {
            struct 
            {
                int x;
                int y;
                int z;
            };
            int c[3];
        };

    public:
        WMVector3Int();
        WMVector3Int(const WMVector3Int& v3i) = default;
        WMVector3Int(WMVector3Int&& v3i) = default;
    };
}
