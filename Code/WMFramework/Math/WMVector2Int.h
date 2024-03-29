//
//  File:   WMVector2Int.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
namespace WildMini
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
