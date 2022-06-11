#pragma once
namespace WildMini::Math
{
    class WMVector3;
    class WMVector4;
    class WMMatrix2;
    class WMVector2
    {
    public:
        union
        {
            struct
            {
                float x;
                float y;
            };
            float c[2];
        };

    public:
        static WMVector2 Normalized(WMVector2 v);
        static float Dot(const WMVector2& v1, const WMVector2& v2);

        const static WMVector2& Left();
        const static WMVector2& Right();
        const static WMVector2& Up();
        const static WMVector2& Down();

    public:
        WMVector2();
        WMVector2(const WMVector3& v);
        WMVector2(WMVector4 v);
        WMVector2(float _x, float _y);
        WMVector2(float xy);

    public:
        float Length();
        float LengthSq();
        void Normalize();

    public:
        bool operator==(const WMVector2& value) const;
        bool operator!=(const WMVector2& value) const;
        WMVector2 operator+(const WMVector2& value) const;
        WMVector2 operator-(const WMVector2& value) const;
        WMVector2 operator*(const float& value) const;
        const WMVector2& operator+=(const WMVector2& value);
        const WMVector2& operator-=(const WMVector2& value);
        const WMVector2& operator*=(const WMVector2& value);
        const WMVector2& operator/=(const WMVector2& value);
        const WMVector2& operator+=(const float& value);
        const WMVector2& operator-=(const float& value);
        const WMVector2& operator*=(const float& value);
        const WMVector2& operator/=(const float& value);
        WMVector2 operator*(const WMMatrix2& value) const;
        WMVector2 operator/(const float& value) const;

    public:
        static const WMVector2 one;
        static const WMVector2 zero;
        static const WMVector2 left;
        static const WMVector2 up;
        static const WMVector2 right;
        static const WMVector2 down;
        static const WMVector2 inf;
        static const WMVector2 negInf;
        static const WMVector2 infLeft;
        static const WMVector2 infUp;
        static const WMVector2 infRight;
        static const WMVector2 infDown;
    };
}
