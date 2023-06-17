//
//  File:   WMSharedPtr.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMContainer.h"
#include "WMRefCounter.h"

namespace WildMini
{
    template<class T>
    class WMSharedPtr
    {
    public:
        WMSharedPtr(T* p = nullptr)
            : object(p)
        {
            InternalAddRef();
        }

        WMSharedPtr(const WMSharedPtr& obj)
            : object(obj.object)
        {
            InternalAddRef();
        }

        WMSharedPtr(const WMSharedPtr&& obj) noexcept
            : object(obj)
        {
            InternalAddRef();
        }

        ~WMSharedPtr() noexcept
        {
            InternalRelease();
        }

        WMSharedPtr& operator=(T* obj)
        {
            if (object != obj)
            {
                InternalRelease();
            }

            object = obj;
            InternalAddRef();
            return *this;
        }

        WMSharedPtr& operator=(const WMSharedPtr& obj) noexcept
        {
            if (object != obj.object)
            {
                InternalRelease();
            }

            object = obj.object;
            InternalAddRef();
            return *this;
        }

        WMSharedPtr& operator=(WMSharedPtr&& obj) noexcept
        {
            if (object != obj.object)
            {
                InternalAddRef();
            }

            object = obj.object;
            obj.object = nullptr;
            return *this;
        }

        template<class U>
        WMSharedPtr<U> DynamicCast()
        {
            return dynamic_cast<U*>(object);
        }

        T* operator->()
        {
            return object;
        }

        const T* operator->() const
        {
            return object;
        }

        T* operator*()
        {
            return object;
        }

        const T* operator*() const
        {
            return object;
        }

        operator T* ()
        {
            return object;
        }

        operator const T* () const
        {
            return object;
        }

        T** operator&()
        {
            return &object;
        }

        T* Ptr()
        {
            return object;
        }

        const T* Ptr() const
        {
            return object;
        }

    private:
        void InternalAddRef()
        {
            if (object)
            {
                object->AddRef();
            }
        }

        void InternalRelease()
        {
            if (object && 0 == object->Release())
            {
                delete object;
                object = nullptr;
            }
        }

    private:
        T* object;
    };
}
