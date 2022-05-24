#pragma once
#include "Common/RefCounter.h"

namespace Core
{
    template<class T>
    class Object
    {
    public:
        Object(T* p = nullptr)
            : object(p)
        {
            InternalAddRef();
        }

        Object(const Object& obj)
            : object(obj.object)
        {
            InternalAddRef();
        }

        Object(const Object&& obj) noexcept
            : object(obj)
        {
            InternalAddRef();
        }

        ~Object() noexcept
        {
            InternalRelease();
        }

        Object& operator=(T* obj)
        {
            if (object != obj)
            {
                InternalRelease();
            }

            object = obj;
            InternalAddRef();
            return *this;
        }

        Object& operator=(const Object& obj) noexcept
        {
            if (object != obj.object)
            {
                InternalRelease();
            }

            object = obj.object;
            InternalAddRef();
            return *this;
        }

        Object& operator=(const Object&& obj) noexcept
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
        Object<U> DynamicCast()
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
