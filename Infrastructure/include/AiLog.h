//HoYoAi
//miHoYo Co., Ltd  All rights reserved
//Created by Haitian.lin  2023/6/6

#pragma once
#include "BaseLibExport.h"
#include <cstdint>
#include <atomic>
#include <stdarg.h>
namespace HoYoAi
{

enum LogLevel
{
    LogLevel_Default,
    LogLevel_Debug,
    LogLevel_Info,
    LogLevel_Warning,
    LogLevel_Error,
};

class AiBaseLibAPI AiLog
{
public:
    //todo: implement log....
    template<typename... Args>
    static void Log(LogLevel logLevel, const char* format, Args... args)
    {
        LogVar(logLevel, format, args...);
    }

    template<typename... Args>
    static void LogInfo(const char* format, Args... args)
    {
        LogVar(LogLevel_Info, format, args...);
    }

    template<typename... Args>
    static void LogWarning(const char* format, Args... args)
    {
        LogVar(LogLevel_Warning, format, args...);
    }

    template<typename... Args>
    static void LogError(const char* format, Args... args)
    {
        LogVar(LogLevel_Error, format, args...);
    }

    static void Log(LogLevel logLevel, const char* str);

	typedef void (*LogFunction)(uint32_t logLevel, const char* str);

	static void SetExternalLogFunction(LogFunction logFunc);
	
    static void CheckColorSupport();

    static void EnableConsoleColorSupport();

private:
    static void LogVar(LogLevel logLevel, const char* format, ...);

	static LogFunction sExteranlLogFunc;
    static uint8_t sLoggineLevel;
    static int8_t sColorFlag; 
    static std::atomic<uint64_t> sWriteFlag;
    static const char* sDebugColor[5];
};

}
