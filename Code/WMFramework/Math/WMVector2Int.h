#pragma once
namespace WildMini::Math
{
    class WMVector2Int
    {
    public:
        union
        {
            struct
            {
                int x;
                int y;
            };
            int c[2];
        };

    public:
        WMVector2Int();
        WMVector2Int(const WMVector2Int& v2i) = default;
        WMVector2Int(WMVector2Int&& v2i) = default;
    };
}
