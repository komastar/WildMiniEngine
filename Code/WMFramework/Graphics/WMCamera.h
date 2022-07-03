//
//  File:   WMCamera.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Math/WMMath.h"

namespace WildMini::Graphics
{
    class WM_API WMCamera
    {
    public:
        WMCamera();

    public:
        void SetView(const WildMini::Math::WMVector3& pos, const WildMini::Math::WMVector3& lookat, const WildMini::Math::WMVector3& up);

        void SetPerspective(float fov, float aspect, float nearZ, float farZ);
        void SetOrthographics(float width, float height, float nearZ, float farZ);

        bool IsPerspective() const;

        float NearZ() const;
        float FarZ() const;
        WildMini::Math::WMVector3 Position() const;
        WildMini::Math::WMMatrix4 ViewMatrix() const;
        WildMini::Math::WMMatrix4 ProjMatrix() const;

    private:
        bool isPerpective;
        float nearZ;
        float farZ;
        WildMini::Math::WMVector3 position;
        WildMini::Math::WMMatrix4 viewMat;
        WildMini::Math::WMMatrix4 projMat;
    };
}
