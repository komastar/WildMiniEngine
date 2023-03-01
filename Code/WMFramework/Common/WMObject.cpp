//
//  File:   WMBase.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "Common/WMObject.h"
#include "Component/WMComponent.h"

using namespace WildMini;

template<typename T>
T* WMObject::AddComponent()
{
    T* comp = new T(this);
    components.push_back(comp);
    return comp;
}

template<typename T>
T* WMObject::GetComponent()
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
