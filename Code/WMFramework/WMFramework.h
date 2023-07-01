//
//  File:   WMFramework.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WildMini.h"
#include "WMContainer.h"
#include "WMAssert.h"
#include "WMLock.h"

#include <stdio.h>

#include <cstdint>
#include <iostream>
#include <atomic>
#include <thread>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <functional>
#include <utility>

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

    template<class T, class Comp = std::greater<void>, class Proj = std::identity>
    const T& Max(const T& obj1, const T& obj2, Comp comp = {}, Proj proj = {})
    {
        return std::invoke(comp, std::invoke(proj, obj1), std::invoke(proj, obj2)) ? obj1 : obj2;
    }

    template<class T, class Comp = std::less<void>, class Proj = std::identity>
    const T& Min(const T& obj1, const T& obj2, Comp comp = {}, Proj proj = {})
    {
        return std::invoke(comp, std::invoke(proj, obj1), std::invoke(proj, obj2)) ? obj1 : obj2;
    }
}
