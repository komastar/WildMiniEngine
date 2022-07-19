#include "WMCamera.h"

using namespace WildMini::Graphics;
using namespace WildMini::Math;

WMCamera::WMCamera()
    : nearZ(0.0f)
    , farZ(0.0f)
    , isPerpective(false)
    , projMat(WMMatrix4::Identity())
{
}

void WMCamera::SetView(const WMVector3& pos, const WMVector3& lookat, const WMVector3& worldUp)
{
    position = pos;
    WMVector3 forward = (lookat - pos).Normalize();
    WMVector3 right = WMVector3::Cross(worldUp, forward).Normalize();
    WMVector3 up = WMVector3::Cross(forward, right).Normalize();

    float x = WMVector3::Dot(-pos, right);
    float y = WMVector3::Dot(-pos, up);
    float z = WMVector3::Dot(-pos, forward);

    viewMat = {
        right.x,    up.x,   forward.x,  0.0f,
        right.y,    up.y,   forward.y,  0.0f,
        right.z,    up.z,   forward.z,  0.0f,
        x,          y,      z,          1.0f
    };
}

void WMCamera::SetPerspective(float fov, float aspect, float nz, float fz)
{
    this->nearZ = nz;
    this->farZ = fz;
    float f = 1.0f / tanf(fov / 2.0f);
    float scale = nearZ / (nearZ - farZ);
    float bias = -farZ * scale;
    projMat = {
        f / aspect, 0.0f,       0.0f,       0.0f,
        0.0f,       f,          0.0f,       0.0f,
        0.0f,       0.0f,       scale,      1.0f,
        0.0f,       0.0f,       bias,       0.0f
    };
    isPerpective = true;
}

void WMCamera::SetOrthographics(float width, float height, float nearZ, float farZ)
{
    this->nearZ = nearZ;
    this->farZ = farZ;
    float range = 1.0f / (farZ - nearZ);
    projMat = {
        2.0f / width,   0.0f,           0.0f,           0.0f,
        0.0f,           2.0f / height,  0.0f,           0.0f,
        0.0f,           0.0f,           range,          1.0f,
        0.0f,           0.0f,           -range * nearZ, 1.0f
    };
    isPerpective = false;
}

bool WMCamera::IsPerspective() const
{
    return isPerpective;
}

float WMCamera::NearZ() const
{
    return nearZ;
}

float WMCamera::FarZ() const
{
    return farZ;
}

WMVector3 WMCamera::Position() const
{
    return position;
}

WMMatrix4 WMCamera::ViewMatrix() const
{
    return viewMat;
}

WMMatrix4 WMCamera::ProjMatrix() const
{
    return projMat;
}
