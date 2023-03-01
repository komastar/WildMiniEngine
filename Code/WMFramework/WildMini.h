//
//  File:   WildMini.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2023 komastar. All rights reserved.
//

#pragma once
#ifdef WM_DYNAMIC
#ifdef DLL_EXPORTS
#define WM_API __declspec(dllexport)
#else
#define WM_API __declspec(dllimport)
#endif // DLL_EXPORTS
#else
#define WM_API
#endif // WM_DYNAMIC
