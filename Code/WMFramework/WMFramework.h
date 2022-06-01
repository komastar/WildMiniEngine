#pragma once
#include <cassert>
#include <cstdint>
#include <iostream>

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

