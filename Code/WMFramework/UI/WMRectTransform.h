#pragma once
#include "WMRefCounter.h"
#include "Graphics/Primitive/WMPoint.h"
#include "Graphics/Primitive/WMSize.h"

namespace WildMini::UI
{
    class WMRectTransform : public WildMini::WMRefCounter
    {
    public:
        WMRectTransform();
        virtual ~WMRectTransform();

    private:
    protected:
        WildMini::Graphics::Primitive::WMPoint position;
        WildMini::Graphics::Primitive::WMSize size;
        WildMini::Graphics::Primitive::WMPoint anchorMin;
        WildMini::Graphics::Primitive::WMPoint anchorMax;
        WildMini::Graphics::Primitive::WMPoint pivot;

    public:
        float GetX();
        float GetLeft();

        float GetY();
        float GetTop();

        float GetWidth();
        float GetRight();

        float GetHeight();
        float GetBottom();
    };
}
