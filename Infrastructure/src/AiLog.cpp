//HoYoAi
//miHoYo Co., Ltd  All rights reserved
//Created by Haitian.lin  2023/6/6

#include "AiLog.h"
#include <cstdio>

#if _WIN32
#include <Windows.h>
#endif

namespace HoYoAi
{
    void AiLog::LogVar(LogLevel logLevel, const char* format, ...)
    {
        static thread_local uint64_t sThreadFlag = (uint64_t)&sThreadFlag;
        static const uint32_t sMaxBufferSize = 4095;
        static char sMessageBuffer[sMaxBufferSize + 1];
        uint64_t sFreeFlag{ 0 };

        LogLevel loglvl = logLevel <= LogLevel_Error ? logLevel : LogLevel_Error;
        if (loglvl >= sLoggineLevel)
        {
            while (!sWriteFlag.compare_exchange_weak(sFreeFlag, sThreadFlag))
            {
            }

            va_list args;
            va_start(args, format);
            if (!sExteranlLogFunc)
            {
#if defined(_WIN32) && _WIN32
                printf("%s", sDebugColor[loglvl]);
                vprintf(format, args);
                printf("%s", sDebugColor[0]);
#else
                printf(format, args...);
#endif
                printf("\n");
            }
            else
            {
                vsnprintf(sMessageBuffer, sMaxBufferSize, format, args);
                sExteranlLogFunc(loglvl, sMessageBuffer);
            }
            va_end(args);

            sWriteFlag.store(sFreeFlag);
        }
    }

AiLog::LogFunction AiLog::sExteranlLogFunc = nullptr;
uint8_t AiLog::sLoggineLevel{ LogLevel_Debug };
int8_t AiLog::sColorFlag{ -1 };
std::atomic<uint64_t> AiLog::sWriteFlag{ 0 };
const char* AiLog::sDebugColor[] =
{
    "\033[0m",
    "\x1B[38;5;33m",
    "\x1B[32;1m",
    "\x1B[38;5;208m",
    "\x1B[31;1m"
};

void AiLog::Log(LogLevel logLevel, const char* str)
{
	if (!str)
		return;

	static thread_local uint64_t sThreadFlag = (uint64_t)&sThreadFlag;
	uint64_t sFreeFlag{ 0 };

	LogLevel loglvl = logLevel <= LogLevel_Error ? logLevel : LogLevel_Error;
	if (loglvl >= sLoggineLevel)
	{
		while (!sWriteFlag.compare_exchange_weak(sFreeFlag, sThreadFlag))
		{
		}

#if _WIN32
		printf("%s%s%s", sDebugColor[loglvl], str, sDebugColor[0]);
#else
		printf("%s", str);
#endif
		printf("\n");
		sWriteFlag.store(sFreeFlag);
	}
}

void AiLog::SetExternalLogFunction(LogFunction logFunc)
{
	sExteranlLogFunc = logFunc;
}

void HoYoAi::AiLog::CheckColorSupport()
{
    sColorFlag = 0;
#if _WIN32
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    if (handle != INVALID_HANDLE_VALUE)
    {
        DWORD mode;
        if (GetConsoleMode(handle, &mode))
        {
            if ((mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) == 0)
            {
                mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(handle, mode);
                sColorFlag = 1;
            }
        }
    }
#endif
}

void AiLog::EnableConsoleColorSupport()
{
#if _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE)
    {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode))
        {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
}

}
