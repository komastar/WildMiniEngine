//
//  File:   WMLog.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
#include "WMFramework.h"
#include "WMLogVariant.h"
#include <vector>

namespace WildMini
{
    enum class WMLogLevel
    {
        Info,
        Debug,
        Warning,
        Error
    };

    template<WMLogLevel>
    void LogString(const char* str);
    template<WMLogLevel>
    void LogString(const wchar_t* wstr);

    template<WMLogLevel, class... Args>
    void LogFormat(const char* format, Args&&... args);
    template<WMLogLevel, class... Args>
    void LogFormat(const wchar_t* format, Args&&... args);

    template<class... Args>
    void WMLogInfo(const char* format, Args&&... args);
    template<class... Args>
    void WMLogInfo(const wchar_t* format, Args&&... args);

    template<class... Args>
    void WMLogDebug(const char* format, Args&&... args);
    template<class... Args>
    void WMLogDebug(const wchar_t* format, Args&&... args);

    template<class... Args>
    void WMLogWarning(const char* format, Args&&... args);
    template<class... Args>
    void WMLogWarning(const wchar_t* format, Args&&... args);

    template<class... Args>
    void WMLogError(const char* format, Args&&... args);
    template<class... Args>
    void WMLogError(const wchar_t* format, Args&&... args);

    void Log(WMLogLevel, const char*, const std::vector<WMLogVariant>&);
    void Log(WMLogLevel, const wchar_t*, const std::vector<WMLogVariant>&);

    template<WMLogLevel level>
    void LogString(const char* str)
    {
        Log(level, str, std::vector<WMLogVariant>());
    }

    template<WMLogLevel level>
    void LogString(const wchar_t* wstr)
    {
        Log(level, wstr, std::vector<WMLogVariant>());
    }

    template<WMLogLevel level, class... Args>
    void LogFormat(const char* format, Args&&... args)
    {
        Log(level, format, std::vector<WMLogVariant>
        {
            WMLogVariant(std::forward<Args>(args))...
        });
    }

    template<WMLogLevel level, class... Args>
    void LogFormat(const wchar_t* format, Args&&... args)
    {
        Log(level, format, std::vector<WMLogVariant>
        {
            WMLogVariant(std::forward<Args>(args))...
        });
    }

    template<class... Args>
    void WMLogInfo(const char* format, Args&&... args)
    {
        LogFormat<WMLogLevel::Info>(format, std::forward<Args>(args)...);
    }

    template<class... Args>
    void WMLogInfo(const wchar_t* format, Args&&... args)
    {
        LogFormat<WMLogLevel::Info>(format, std::forward<Args>(args)...);
    }

    template<class... Args>
    void WMLogDebug(const char* format, Args&&... args)
    {
        LogFormat<WMLogLevel::Debug>(format, std::forward<Args>(args)...);
    }

    template<class... Args>
    void WMLogDebug(const wchar_t* format, Args&&... args)
    {
        LogFormat<WMLogLevel::Debug>(format, std::forward<Args>(args)...);
    }

    template<class... Args>
    void WMLogWarning(const char* format, Args&&... args)
    {
        LogFormat<WMLogLevel::Warning>(format, std::forward<Args>(args)...);
    }

    template<class... Args>
    void WMLogWarning(const wchar_t* format, Args&&... args)
    {
        LogFormat<WMLogLevel::Warning>(format, std::forward<Args>(args)...);
    }

    template<class... Args>
    void WMLogError(const char* format, Args&&... args)
    {
        LogFormat<WMLogLevel::Error>(format, std::forward<Args>(args)...);
    }

    template<class... Args>
    void WMLogError(const wchar_t* format, Args&&... args)
    {
        LogFormat<WMLogLevel::Error>(format, std::forward<Args>(args)...);
    }
}
