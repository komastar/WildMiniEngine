//
//  File:   WMVector3.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
namespace WildMini::Math
{
    class WMVector2;
    class WMVector4;
    class WMMatrix3;
    class WMVector3
    {
    public:
        union
        {
            struct
            {
                float x;
                float y;
                float z;
            };
            float c[3];
        };

    public:
        static WMVector3 Normalized(WMVector3 v);
        static float Dot(const WMVector3& v1, const WMVector3& v2);
        static WMVector3 Cross(const WMVector3& v1, const WMVector3& v2);

        static const WMVector3& Forward();
        static const WMVector3& Backward();
        static const WMVector3& Left();
        static const WMVector3& Right();
        static const WMVector3& Up();
        static const WMVector3& Down();

    public:
        WMVector3();
        WMVector3(WMVector2 v);
        WMVector3(WMVector4 v);
        WMVector3(float _x, float _y);
        WMVector3(float _x, float _y, float _z);
        WMVector3(float xyz);

    public:
        float Length();
        float LengthSq();
        const WMVector3& Normalize();

    public:
        bool operator==(const WMVector3& value) const;
        bool operator!=(const WMVector3& value) const;
        WMVector3 operator+(const WMVector3& value) const;
        WMVector3 operator-(const WMVector3& value) const;
        WMVector3 operator-() const;
        WMVector3 operator*(const float& value) const;
        WMVector3 operator*(const WMMatrix3& value) const;
        WMVector3 operator/(const float& value) const;

    public:
        static const WMVector3 one;
        static const WMVector3 zero;
        static const WMVector3 left;
        static const WMVector3 up;
        static const WMVector3 right;
        static const WMVector3 down;
        static const WMVector3 forward;
        static const WMVector3 back;
    };
}
