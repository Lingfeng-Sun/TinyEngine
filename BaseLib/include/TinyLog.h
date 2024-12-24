#pragma once

#include <cstdint>
#include <atomic>
#include <stdarg.h>
#include "Global.h"

namespace ty
{

enum LogLevel : uint8_t
{
    LogLevel_Default,
    LogLevel_Debug,
    LogLevel_Info,
    LogLevel_Warning,
    LogLevel_Error,
};

class TyLog : public SingletonObject
{
public:
    //todo: implement log....
    template<typename... Args>
    static void Log(LogLevel logLevel, const char* format, Args... args)
    {
        Instance()->LogVar(logLevel, format, args...);
    }

    template<typename... Args>
    static void LogInfo(const char* format, Args... args)
    {
        Instance()->LogVar(LogLevel_Info, format, args...);
    }

    template<typename... Args>
    static void LogWarning(const char* format, Args... args)
    {
        Instance()->LogVar(LogLevel_Warning, format, args...);
    }

    template<typename... Args>
    static void LogError(const char* format, Args... args)
    {
        Instance()->LogVar(LogLevel_Error, format, args...);
    }

    static void Log(LogLevel logLevel, const char* str);

	typedef void (*LogFunction)(uint32_t logLevel, const char* str);

	static void SetExternalLogFunction(LogFunction logFunc);

    

    virtual void Release() override;

private:
    void LogVar(LogLevel logLevel, const char* format, ...);

    static TyLog* Instance();

    LogFunction mExteranlLogFunc{ nullptr };
    int8_t mLoggineLevel{ LogLevel_Debug };
    std::atomic<uint64_t> mWriteFlag{ 0 };
};

}
