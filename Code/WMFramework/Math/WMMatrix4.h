//
//  File:   WMMatrix4.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
namespace WildMini
{
    class WMVector3;
    class WMMatrix2;
    class WMMatrix3;
    class WMMatrix4
    {
    public:
        union
        {
            struct
            {
                float _11, _12, _13, _14;
                float _21, _22, _23, _24;
                float _31, _32, _33, _34;
                float _41, _42, _43, _44;
            };
            float m[4][4];
            float v[16];
        };

    public:
        static WMMatrix4 Inversed(WMMatrix4& m);
        static WMMatrix4 Identity();
        static WMMatrix4 Transposed(WMMatrix4& m);

    public:
        WMMatrix4();
        WMMatrix4(float _11, float _12, float _13, float _14
            , float _21, float _22, float _23, float _24
            , float _31, float _32, float _33, float _34
            , float _41, float _42, float _43, float _44);
        WMMatrix4(const WMMatrix2& m);
        WMMatrix4(const WMMatrix3& m);

    public:
        WMMatrix4 Transpose();
        WMMatrix4 Inverse();
        const WMMatrix4& View(const WMVector3& eye, const WMVector3& lookat, const WMVector3& up);
        const WMMatrix4& Projection(float fov, float aspect, float nearZ, float farZ);
        const WMMatrix4& Viewport(float x, float y, float w, float h, float minZ, float maxZ);

    private:
        float Determinant();
        WMMatrix4 Adjoint();
        float Cofactor(int y, int x);
        float Minor(int y, int x);

    public:
        bool operator==(const WMMatrix4& value) const;
        bool operator!=(const WMMatrix4& value) const;
        WMMatrix4 operator+(const WMMatrix4& value) const;
        WMMatrix4 operator-(const WMMatrix4& value) const;
        WMMatrix4 operator*(const WMMatrix4& value) const;
        WMMatrix4 operator*(const float& value) const;
    };
}
