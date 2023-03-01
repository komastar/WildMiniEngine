//
//  File:   WMCamera.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Math/WMMath.h"

namespace WildMini
{
    class WM_API WMCamera
    {
    public:
        WMCamera();

    public:
        void SetView(const WMVector3& pos, const WMVector3& lookat, const WMVector3& up);

        void SetPerspective(float fov, float aspect, float nearZ, float farZ);
        void SetOrthographics(float width, float height, float nearZ, float farZ);

        bool IsPerspective() const;

        float NearZ() const;
        float FarZ() const;
        WMVector3 Position() const;
        WMMatrix4 ViewMatrix() const;
        WMMatrix4 ProjMatrix() const;

    private:
        bool isPerpective;
        float nearZ;
        float farZ;
        WMVector3 position;
        WMMatrix4 viewMat;
        WMMatrix4 projMat;
    };
}
