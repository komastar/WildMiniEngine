//
//  File:   WMContainer.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include <atomic>
#include <cstdint>
#include <vector>
#include <array>
#include <string>
#include <map>

template<typename T>
using Vector = std::vector<T>;

template<typename TK, typename TV>
using Map = std::map<TK, TV>;

using WMTick = uint64_t;

using WMString = std::wstring;
