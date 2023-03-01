//
//  File:   WMMatrix2.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMMatrix3.h"
#include "WMMatrix4.h"

namespace WildMini
{
    class WMMatrix3;
    class WMMatrix4;
    class WMMatrix2
    {
    public:
        union
        {
            struct
            {
                float _11, _12;
                float _21, _22;
            };
            float m[2][2];
            float v[4];
        };

    public:
        static WMMatrix2 Inversed(WMMatrix2& m);
        static WMMatrix2 Identity();

    public:
        WMMatrix2();
        WMMatrix2(float _11, float _12, float _21, float _22);
        WMMatrix2(const WMMatrix3& m);
        WMMatrix2(const WMMatrix4& m);

    public:
        WMMatrix2 Transpose();
        WMMatrix2 Inverse();

    public:
        void Scale(float x, float y);

    private:
        float Determinant();

    public:
        bool operator==(const WMMatrix2& value) const;
        bool operator!=(const WMMatrix2& value) const;
        WMMatrix2 operator+(const WMMatrix2& value) const;
        WMMatrix2 operator-(const WMMatrix2& value) const;
        WMMatrix2 operator*(const WMMatrix2& value) const;
        WMMatrix2 operator*(const float& value) const;
    };
}
