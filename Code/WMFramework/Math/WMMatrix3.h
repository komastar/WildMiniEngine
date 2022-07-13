//
//  File:   WMMatrix3.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
namespace WildMini::Math
{
    class WMMatrix2;
    class WMMatrix4;
    class WMMatrix3
    {
    public:
        union
        {
            struct
            {
                float _11, _12, _13;
                float _21, _22, _23;
                float _31, _32, _33;
            };
            float m[3][3];
            float v[9];
        };

    public:
        static WMMatrix3 Inversed(WMMatrix3& m);
        static WMMatrix3 Identity();
        static WMMatrix3 Transposed(WMMatrix3& m);

    public:
        WMMatrix3();
        WMMatrix3(float _11, float _12, float _13
            , float _21, float _22, float _23
            , float _31, float _32, float _33);
        WMMatrix3(const WMMatrix2& m);
        WMMatrix3(const WMMatrix4& m);

    public:
        void Transpose();
        WMMatrix3 Inverse();

    private:
        float Determinant();
        WMMatrix3 Adjoint();
        float Cofactor(int y, int x);
        float Minor(int y, int x);

    public:
        bool operator==(const WMMatrix3& value) const;
        bool operator!=(const WMMatrix3& value) const;
        WMMatrix3 operator+(const WMMatrix3& value) const;
        WMMatrix3 operator-(const WMMatrix3& value) const;
        WMMatrix3 operator*(const WMMatrix3& value) const;
        WMMatrix3 operator*(const float& value) const;
    };
}
