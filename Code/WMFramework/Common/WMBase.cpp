//
//  File:   WMBase.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMBase.h"

using namespace WildMini;

template<typename T>
T* WMBase::AddComponent()
{
    T* comp = new T();
    components.push_back(comp);
    return comp;
}

template<typename T>
T* WMBase::GetComponent()
{
    for (auto& component : components)
    {
        if (WMComponent* find = dynamic_cast<T*>(component))
        {
            return find;
        }
    }

    return nullptr;
}
