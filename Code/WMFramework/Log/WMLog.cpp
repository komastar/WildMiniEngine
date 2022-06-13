#include "WMLog.h"
#include <fmt/args.h>
#include <fmt/format.h>
#include <fmt/xchar.h>
#include <fmt/color.h>

using namespace WildMini;

std::string Now()
{
    time_t now = time(0);
    struct tm tstruct;
#ifdef WIN32
    localtime_s(&tstruct, &now);
#elif __APPLE__
    localtime_r(&now, &tstruct);
#endif
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d.%x", &tstruct);
    return buf;
}

std::wstring NowW()
{
    time_t now = time(0);
    struct tm tstruct;
#ifdef WIN32
    localtime_s(&tstruct, &now);
#elif __APPLE__
    localtime_r(&now, &tstruct);
#endif
    wchar_t buf[80];
    wcsftime(buf, sizeof(buf), L"%Y-%m-%d.%x", &tstruct);
    return buf;
}

std::string LogLevelToString(WMLogLevel level)
{
    switch (level)
    {
    case WildMini::WMLogLevel::Info:
        return "INFO";
    case WildMini::WMLogLevel::Debug:
        return "DEBUG";
    case WildMini::WMLogLevel::Warning:
        return "WARNING";
    case WildMini::WMLogLevel::Error:
        return "ERROR";
    }
    return "NONE";
}

std::wstring LogLevelToStringW(WMLogLevel level)
{
    switch (level)
    {
    case WildMini::WMLogLevel::Info:
        return L"INFO";
    case WildMini::WMLogLevel::Debug:
        return L"DEBUG";
    case WildMini::WMLogLevel::Warning:
        return L"WARNING";
    case WildMini::WMLogLevel::Error:
        return L"ERROR";
    }
    return L"NONE";
}

fmt::text_style LogLevelToStyle(WMLogLevel level)
{
    switch (level)
    {
    case WildMini::WMLogLevel::Info:
        return fg(fmt::color::beige);
    case WildMini::WMLogLevel::Debug:
        return fg(fmt::color::dark_orange);
    case WildMini::WMLogLevel::Warning:
        return fg(fmt::color::yellow);
    case WildMini::WMLogLevel::Error:
        return fg(fmt::color::white) | bg(fmt::color::dark_red);
    }

    return fg(fmt::color::white);
}

void LogPrint(WMLogLevel level, const char* log)
{
    fmt::text_style style = LogLevelToStyle(level);
    fmt::print(stdout, style, "[{}] [{}] {}\n", Now(), LogLevelToString(level), log);
}

void LogPrint(WMLogLevel level, const wchar_t* log)
{
    auto style = LogLevelToStyle(level);
    fmt::print(stdout, style, L"[{}] [{}] {}\n", NowW(), LogLevelToStringW(level), log);
}

void WildMini::Log(WMLogLevel level, const char* format, const std::vector<WMLogVariant>& args)
{
    fmt::dynamic_format_arg_store<fmt::buffer_context<char>> dynamicArgs;
    for (WMLogVariant v : args)
    {
        switch (v.GetType())
        {
        case WMLogVariant::Type::BOOL:
            dynamicArgs.push_back(v.Boolean());
            break;
        case WMLogVariant::Type::INT32:
            dynamicArgs.push_back(v.Int32());
            break;
        case WMLogVariant::Type::INT64:
            dynamicArgs.push_back(v.Int64());
            break;
        case WMLogVariant::Type::UINT32:
            dynamicArgs.push_back(v.UInt32());
            break;
        case WMLogVariant::Type::UINT64:
            dynamicArgs.push_back(v.UInt64());
            break;
        case WMLogVariant::Type::LONG:
            dynamicArgs.push_back(v.Long());
            break;
        case WMLogVariant::Type::ULONG:
            dynamicArgs.push_back(v.ULong());
            break;
        case WMLogVariant::Type::FLOAT:
            dynamicArgs.push_back(v.Float());
            break;
        case WMLogVariant::Type::DOUBLE:
            dynamicArgs.push_back(v.Double());
            break;
        case WMLogVariant::Type::CHAR:
            dynamicArgs.push_back(v.Char());
            break;
        case WMLogVariant::Type::WCHAR:
            WMASSERT_DESC(false, "WCHAR NOT SUPPORTED");
            break;
        case WMLogVariant::Type::NONE:
            WMASSERT_DESC(false, "NONE NOT SUPPORTED");
            break;
        }
    }
    LogPrint(level, fmt::vformat(format, dynamicArgs).c_str());
}

void WildMini::Log(WMLogLevel level, const wchar_t* format, const std::vector<WMLogVariant>& args)
{
    fmt::dynamic_format_arg_store<fmt::buffer_context<wchar_t>> dynamicArgs;
    for (WMLogVariant v : args)
    {
        switch (v.GetType())
        {
        case WMLogVariant::Type::BOOL:
            dynamicArgs.push_back(v.Boolean());
            break;
        case WMLogVariant::Type::INT32:
            dynamicArgs.push_back(v.Int32());
            break;
        case WMLogVariant::Type::INT64:
            dynamicArgs.push_back(v.Int64());
            break;
        case WMLogVariant::Type::UINT32:
            dynamicArgs.push_back(v.UInt32());
            break;
        case WMLogVariant::Type::UINT64:
            dynamicArgs.push_back(v.UInt64());
            break;
        case WMLogVariant::Type::LONG:
            dynamicArgs.push_back(v.Long());
            break;
        case WMLogVariant::Type::ULONG:
            dynamicArgs.push_back(v.ULong());
            break;
        case WMLogVariant::Type::FLOAT:
            dynamicArgs.push_back(v.Float());
            break;
        case WMLogVariant::Type::DOUBLE:
            dynamicArgs.push_back(v.Double());
            break;
        case WMLogVariant::Type::CHAR:
            WMASSERT_DESC(false, "CHAR NOT SUPPORTED");            
            break;
        case WMLogVariant::Type::WCHAR:
            dynamicArgs.push_back(v.WChar());
            break;
        case WMLogVariant::Type::NONE:
            WMASSERT_DESC(false, "NONE NOT SUPPORTED");
            break;
        }
    }
    LogPrint(level, fmt::vformat<wchar_t>(format, dynamicArgs).c_str());
}
