//
//  File:   WMAssert.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#include <cassert>

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
