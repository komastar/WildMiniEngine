#include "WMLogVariant.h"

using namespace WildMini;

WMLogVariant::WMLogVariant()
    : type(Type::NONE)
    , data{ 0 }
{
}

WMLogVariant::WMLogVariant(const bool v)
    : type(Type::BOOL)
    , data{ 0 }
{
    new (data) bool(v);
}

WMLogVariant::WMLogVariant(const int32_t v)
    : type(Type::INT32)
    , data{ 0 }
{
    new (data) int32_t(v);
}

WMLogVariant::WMLogVariant(const int64_t v)
    : type(Type::INT64)
    , data{ 0 }
{
    new (data) int64_t(v);
}

WMLogVariant::WMLogVariant(const uint32_t v)
    : type(Type::UINT32)
    , data{ 0 }
{
    new (data) uint32_t(v);
}

WMLogVariant::WMLogVariant(const uint64_t v)
    : type(Type::UINT64)
    , data{ 0 }
{
    new (data) uint64_t(v);
}

WMLogVariant::WMLogVariant(const long v)
    : type(Type::LONG)
    , data{ 0 }
{
    new (data) long(v);
}

WMLogVariant::WMLogVariant(const unsigned long v)
    : type(Type::ULONG)
    , data{ 0 }
{
    new (data) unsigned long(v);
}

WMLogVariant::WMLogVariant(const float v)
    : type(Type::FLOAT)
    , data{ 0 }
{
    new (data) float(v);
}

WMLogVariant::WMLogVariant(const double v)
    : type(Type::DOUBLE)
    , data{ 0 }
{
    new (data) double(v);
}

WMLogVariant::WMLogVariant(const long double v)
    : type(Type::DOUBLE)
    , data{ 0 }
{
    new (data) long double(v);
}

WMLogVariant::WMLogVariant(const char* v)
    : type(Type::CHAR)
    , data{ 0 }
{
    new (data) const char* (v);
}

WMLogVariant::WMLogVariant(const wchar_t* v)
    : type(Type::WCHAR)
    , data{ 0 }
{
    new (data) const wchar_t* (v);
}

WMLogVariant::WMLogVariant(const void* v)
    : WMLogVariant(reinterpret_cast<uintptr_t>(v))
{
}

bool WMLogVariant::Boolean()
{
    WMASSERT(Type::BOOL == type);
    return reinterpret_cast<bool*>(data)[0];
}

int32_t WMLogVariant::Int32()
{
    WMASSERT(Type::INT32 == type);
    return reinterpret_cast<int32_t*>(data)[0];
}

int64_t WMLogVariant::Int64()
{
    WMASSERT(Type::INT64 == type);
    return reinterpret_cast<int64_t*>(data)[0];
}

uint32_t WMLogVariant::UInt32()
{
    WMASSERT(Type::UINT32 == type);
    return reinterpret_cast<uint32_t*>(data)[0];
}

uint64_t WMLogVariant::UInt64()
{
    WMASSERT(Type::UINT64 == type);
    return reinterpret_cast<uint64_t*>(data)[0];
}

long WMLogVariant::Long()
{
    WMASSERT(Type::LONG == type);
    return reinterpret_cast<long*>(data)[0];
}

unsigned long WMLogVariant::ULong()
{
    WMASSERT(Type::ULONG == type);
    return reinterpret_cast<unsigned long*>(data)[0];
}

float WMLogVariant::Float()
{
    WMASSERT(Type::FLOAT == type);
    return reinterpret_cast<float*>(data)[0];
}

double WMLogVariant::Double()
{
    WMASSERT(Type::DOUBLE == type);
    return reinterpret_cast<double*>(data)[0];
}

const char* WMLogVariant::Char()
{
    WMASSERT(Type::CHAR == type);
    return reinterpret_cast<const char**>(data)[0];
}

const wchar_t* WMLogVariant::WChar()
{
    WMASSERT(Type::WCHAR == type);
    return reinterpret_cast<const wchar_t**>(data)[0];
}

WMLogVariant::Type WMLogVariant::GetType()
{
    return type;
}
