#pragma once
#include "WMRefCounter.h"

namespace WildMini::Object
{
    template<class T>
    class WMObject
    {
    public:
        WMObject(T* p = nullptr)
            : object(p)
        {
            InternalAddRef();
        }

        WMObject(const WMObject& obj)
            : object(obj.object)
        {
            InternalAddRef();
        }

        WMObject(const WMObject&& obj) noexcept
            : object(obj)
        {
            InternalAddRef();
        }

        ~WMObject() noexcept
        {
            InternalRelease();
        }

        WMObject& operator=(T* obj)
        {
            if (object != obj)
            {
                InternalRelease();
            }

            object = obj;
            InternalAddRef();
            return *this;
        }

        WMObject& operator=(const WMObject& obj) noexcept
        {
            if (object != obj.object)
            {
                InternalRelease();
            }

            object = obj.object;
            InternalAddRef();
            return *this;
        }

        WMObject& operator=(const WMObject&& obj) noexcept
        {
            if (object != obj->object)
            {
                InternalAddRef();
            }

            object = obj->object;
            obj->object = nullptr;
            return *this;
        }

        template<class U>
        WMObject<U> DynamicCast()
        {
            return dynamic_cast<U>(object);
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
