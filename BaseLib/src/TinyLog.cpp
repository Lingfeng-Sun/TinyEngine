#include "TinyLog.h"
#include <cstdio>

namespace ty
{

SingletonObject* CreateInstance(void*)
{
    return new TyLog();
}

TyLog* TyLog::Instance()
{
    static TyLog* sInstance = static_cast<TyLog*>(Global::RegisterSingletonObject<TyLog>(CreateSingletonParam{ CreateInstance,nullptr }));
    return sInstance;
}

void TyLog::Release()
{
    delete this;
}

void TyLog::LogVar(LogLevel logLevel, const char* format, ...)
{
    static thread_local uint64_t sThreadFlag = (uint64_t)&sThreadFlag;
    static const uint32_t sMaxBufferSize = 4095;
    static char sMessageBuffer[sMaxBufferSize + 1];
    uint64_t sFreeFlag{ 0 };

    LogLevel loglvl = logLevel <= LogLevel_Error ? logLevel : LogLevel_Error;
    if ((int8_t)loglvl >= mLoggineLevel)
    {
        while (!mWriteFlag.compare_exchange_weak(sFreeFlag, sThreadFlag))
        {
        }

        va_list args;
        va_start(args, format);
        if (!mExteranlLogFunc)
        {
            vprintf(format, args);
            printf("\n");
        }
        else
        {
            vsnprintf(sMessageBuffer, sMaxBufferSize, format, args);
            mExteranlLogFunc(loglvl, sMessageBuffer);
        }
        va_end(args);

        mWriteFlag.store(sFreeFlag);
    }
}

void TyLog::Log(LogLevel logLevel, const char* str)
{
    if (!str)
        return;

    static thread_local uint64_t sThreadFlag = (uint64_t)&sThreadFlag;
    uint64_t sFreeFlag{ 0 };

    LogLevel loglvl = logLevel <= LogLevel_Error ? logLevel : LogLevel_Error;
    if ((int8_t)loglvl >= Instance()->mLoggineLevel)
    {
        while (!Instance()->mWriteFlag.compare_exchange_weak(sFreeFlag, sThreadFlag))
        {
        }

        printf("%s", str);
        printf("\n");
        Instance()->mWriteFlag.store(sFreeFlag);
    }
}

void TyLog::SetExternalLogFunction(LogFunction logFunc)
{
    Instance()->mExteranlLogFunc = logFunc;
}

}
