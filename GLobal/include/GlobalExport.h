#pragma once

#if defined(_WIN32)
    #ifdef Global_EXPORTS
        #define GlobalAPI __declspec(dllexport)
    #else
        #define GlobalAPI __declspec(dllimport)
    #endif
#else
    #define GlobalAPI
#endif

