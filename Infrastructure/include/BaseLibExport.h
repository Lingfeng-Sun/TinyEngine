//HoYoAi
//miHoYo Co., Ltd  All rights reserved
//Created by Haitian.lin  2023/6/6
#pragma once

#if defined(_WIN32) && defined(HOYOAI_BUILD_DYNAMIC_LIB)
    #ifdef AiBaseLib_EXPORTS
        #define AiBaseLibAPI __declspec(dllexport)
    #else
        #define AiBaseLibAPI __declspec(dllimport)
    #endif
#else
    #define AiBaseLibAPI
#endif

