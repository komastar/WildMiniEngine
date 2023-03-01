//
//  File:   WMLock.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include <mutex>

using WMMutex = std::mutex;

template <typename T>
using WMLockGuard = std::lock_guard<T>;
