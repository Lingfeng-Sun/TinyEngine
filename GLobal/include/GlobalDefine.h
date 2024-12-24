//HoYoAi
//miHoYo Co., Ltd  All rights reserved
//Created by Haitian.lin  2023/6/6

#pragma once
#include <csignal>

//////////////////////////////////////////////////////////////////////////
/*
MI_INLINE
MI_FORCEINLINE
MI_NOINLINE
MI_DEBUGNOINLINE
*/

#define AI_INLINE inline

#ifdef _MSC_VER
    #define AI_FORCEINLINE __forceinline
    #define AI_NOINLINE __declspec(noinline)
#elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
    #define AI_FORCEINLINE __attribute__((always_inline))
    #define AI_NOINLINE __attribute__(noinline)
#else
    //if defined(__clang__)....
    #error implement MI_FORCEINLINE for other compioler
#endif

#ifdef NDEBUG
    #define AI_DEBUGNOINLINE AI_INLINE
#else
    #define AI_DEBUGNOINLINE AI_NOINLINE
#endif

//////////////////////////////////////////////////////////////////////////
//class helper
#define AI_NON_COPY_CLASS(Type)\
Type(const Type&) = delete;\
Type& operator=(const Type&) = delete;\

//////////////////////////////////////////////////////////////////////////
//helper function for vector
#define AI_ADD_UNIQUE(vector, value)\
for(auto& v : vector)\
{\
    if (v == value)\
        return;\
}\
vector.emplace_back(value);


//////////////////////////////////////////////////////////////////////////
//helper function for map
#define AI_GET_MAP_VALUE(map, key, defaultValue)\
auto it = map.find(key);\
if(it != map.end())\
{\
    return it->second;\
}\
return defaultValue;

#define AI_GET_MAP_HAS_VALUE(map, key)\
auto it = map.find(key);\
return it != map.end()


//////////////////////////////////////////////////////////////////////////
//break point
#ifdef _MSC_VER
    #define AI_BREAK_POINT  __debugbreak();
#else
    #define AI_BREAK_POINT  std::raise(SIGINT);
#endif


#define AI_FUNC_NOT_IMP AI_BREAK_POINT

#define D2F(value) (float)value

