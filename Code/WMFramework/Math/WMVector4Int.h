//
//  File:   WMVector4Int.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
namespace WildMini
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
