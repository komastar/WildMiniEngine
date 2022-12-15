//
//  File:   WMBase.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "Object/WMRefCounter.h"
#include "Common/WMComponent.h"

namespace WildMini
{
    class WM_API WMBase : public Object::WMRefCounter
    {
    public:
        template<typename T>
        T* AddComponent();

        template<typename T>
        T* GetComponent();

    private:
        std::wstring name;
        std::wstring uuid;
        std::vector<WMComponent*> components;
    };
}