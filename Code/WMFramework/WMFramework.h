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
}
