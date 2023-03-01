//
//  File:   WMVector3Int.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
namespace WildMini
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
