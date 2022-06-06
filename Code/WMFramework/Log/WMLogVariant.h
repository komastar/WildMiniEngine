#pragma once
#include "WMFramework.h"

namespace WildMini
{
    class WM_API WMLogVariant
    {
    public:
        enum class Type : int
        {
            NONE = 0,
            BOOL,
            INT32,
            INT64,
            UINT32,
            UINT64,
            LONG,
            ULONG,
            FLOAT,
            DOUBLE,
            CHAR,
            WCHAR
        };

        WMLogVariant();
        WMLogVariant(const WMLogVariant& v) = default;
        WMLogVariant(WMLogVariant&& v) = default;
        WMLogVariant(const bool v);
        WMLogVariant(const int32_t v);
        WMLogVariant(const int64_t v);
        WMLogVariant(const uint32_t v);
        WMLogVariant(const uint64_t v);
        WMLogVariant(const long v);
        WMLogVariant(const unsigned long v);
        WMLogVariant(const float v);
        WMLogVariant(const double v);
        WMLogVariant(const long double v);
        WMLogVariant(const char* v);
        WMLogVariant(const wchar_t* v);
        WMLogVariant(const void* v);

        bool Boolean();
        int32_t Int32();
        int64_t Int64();
        uint32_t UInt32();
        uint64_t UInt64();
        long Long();
        unsigned long ULong();
        float Float();
        double Double();
        const char* Char();
        const wchar_t* WChar();

        Type GetType();

    private:
        Type type;
        unsigned char data[sizeof(void*)];;
    };
}
