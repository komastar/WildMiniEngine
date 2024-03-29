//
//  File:   WMBase.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMRefCounter.h"

namespace WildMini
{
    class WMComponent;
    class WM_API WMObject : public WMRefCounter
    {
    public:
        template<typename T>
        T* AddComponent();

        template<typename T>
        T* GetComponent();

    private:
        std::wstring name;
        std::wstring uuid;
        Vector<WMComponent*> components;
    };
}
