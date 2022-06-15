//
//  File:   WMFramework.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include <vector>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <atomic>

#ifdef WM_DYNAMIC
    #ifdef DLL_EXPORTS
        #define WM_API __declspec(dllexport)
    #else
        #define WM_API __declspec(dllimport)
    #endif // DLL_EXPORTS
#else
    #define WM_API
#endif // WM_DYNAMIC

#define WM_NOOP                             (void)0;

#define _WMASSERT(expr)                     assert(expr)
#define _WMASSERT_DESC(expr, desc)          assert(((void)desc, expr))

#ifdef _DEBUG
#define WMASSERT(expr)                      _WMASSERT(expr)
#define WMASSERT_DESC(expr, desc)           _WMASSERT_DESC(expr, desc)
#else
#define WMASSERT(expr)                      WM_NOOP
#define WMASSERT_DESC(expr, desc)           WM_NOOP
#endif // _DEBUG

namespace WildMini
{
    template<class T>
    concept Arithmetic = std::is_arithmetic_v<T>;

    template<class T, class U>
    constexpr decltype(auto) Min(const T& a, const U& b) noexcept
    {
        return (a < b) ? a : b;
    }

    template<class T, class U, class... V>
    constexpr decltype(auto) Min(const T& a, const U& b, const V&... args) noexcept
    {
        return Min(a, Min(b, args...));
    }

    template<class T, class U>
    constexpr decltype(auto) Max(const T& a, const U& b) noexcept
    {
        return (a > b) ? a : b;
    }

    template<class T, class U, class... V>
    constexpr decltype(auto) Max(const T& a, const U& b, const V&... args) noexcept
    {
        return Max(a, Max(b, args...));
    }

    template<class T>
    constexpr decltype(auto) Clamp(const T& value, const T& min, const T& max) noexcept
    {
        return value < min ? min : value > max ? max : value;
    }
}
