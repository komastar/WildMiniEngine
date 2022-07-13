//
//  File:   WMVector4.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
namespace WildMini::Math
{
    class WMVector2;
    class WMVector3;
    class WMMatrix4;
    class WMVector4
    {
    public:
        union
        {
            struct
            {
                float x;
                float y;
                float z;
                float w;
            };
            float c[4];
        };

    public:
        static WMVector4 Normalized(WMVector4 v);
        static float Dot(const WMVector4& v1, const WMVector4& v2);

        static const WMVector4& Forward();
        static const WMVector4& Backward();
        static const WMVector4& Left();
        static const WMVector4& Right();
        static const WMVector4& Up();
        static const WMVector4& Down();

    public:
        WMVector4();
        WMVector4(WMVector2 v);
        WMVector4(WMVector3 v);
        WMVector4(float _x, float _y);
        WMVector4(float _x, float _y, float _z);
        WMVector4(float _x, float _y, float _z, float _w);
        WMVector4(float xyzw);

    public:
        float Length();
        float LengthSq();
        void Normalize();

    public:
        bool operator==(const WMVector4& value) const;
        bool operator!=(const WMVector4& value) const;
        WMVector4 operator+(const WMVector4& value) const;
        WMVector4 operator-(const WMVector4& value) const;
        WMVector4 operator*(const float& value) const;
        WMVector4 operator*(const WMMatrix4& value) const;
        WMVector4 operator/(const float& value) const;

    public:
        static const WMVector4 one;
        static const WMVector4 zero;
        static const WMVector4 left;
        static const WMVector4 up;
        static const WMVector4 right;
        static const WMVector4 down;
        static const WMVector4 back;
        static const WMVector4 forward;
    };
}
