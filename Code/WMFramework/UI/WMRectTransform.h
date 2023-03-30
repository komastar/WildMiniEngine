//
//  File:   WMRectTransform.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include "WMRefCounter.h"
#include "Graphics/Primitive/WMPoint.h"
#include "Graphics/Primitive/WMSize.h"

namespace WildMini
{
    class WMRectTransform : public WMRefCounter
    {
    public:
        WMRectTransform();
        virtual ~WMRectTransform();

    private:
    protected:
        WMPoint position;
        WMSize size;
        WMPoint anchorMin;
        WMPoint anchorMax;
        WMPoint pivot;

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
