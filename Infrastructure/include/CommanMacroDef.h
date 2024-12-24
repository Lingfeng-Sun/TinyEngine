

#pragma once
#include <csignal>

//////////////////////////////////////////////////////////////////////////
/*
INLINE
FORCEINLINE
NOINLINE
DEBUGNOINLINE
*/

#define TY_INLINE inline

#ifdef _MSC_VER
#define TY_FORCEINLINE __forceinline
#define TY_NOINLINE __declspec(noinline)
#elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
#define TY_FORCEINLINE __attribute__((always_inline))
#define TY_NOINLINE __attribute__(noinline)
#else
//if defined(__clang__)....
#error implement MI_FORCEINLINE for other compioler
#endif

#ifdef NDEBUG
#define TY_DEBUGNOINLINE TY_INLINE
#else
#define TY_DEBUGNOINLINE TY_NOINLINE
#endif


//////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#define ty_aligned_malloc(size, alignment) _aligned_malloc(size, alignment)
#define ty_aligned_free(ptr) _aligned_free(ptr)
#else
#define ty_aligned_malloc(size, alignment) aligned_alloc(alignment, size)
#define ty_aligned_free(ptr) free(ptr)
#endif

//////////////////////////////////////////////////////////////////////////
#ifdef TINY_SHIPPING
template <class T, class U>
AI_INLINE T TypeCast(U& r) noexcept
{
    return (T)r;
}
#else
template <class T, class U>
TY_INLINE T TypeCast(U& r) noexcept
{
    return dynamic_cast<T>(r);
}
#endif



//////////////////////////////////////////////////////////////////////////
//class helper
#define TY_NON_COPY_CLASS(Type)\
Type(const Type&) = delete;\
Type& operator=(const Type&) = delete;\

//////////////////////////////////////////////////////////////////////////
//helper function for vector
#define TY_ADD_UNIQUE(vector, value)\
for(auto& v : vector)\
{\
    if (v == value)\
        return;\
}\
vector.emplace_back(value);


//////////////////////////////////////////////////////////////////////////
//helper function for map
#define TY_GET_MAP_VALUE(map, key, defaultValue)\
auto it = map.find(key);\
if(it != map.end())\
{\
    return it->second;\
}\
return defaultValue;

#define TY_GET_MAP_HAS_VALUE(map, key)\
auto it = map.find(key);\
return it != map.end()


//////////////////////////////////////////////////////////////////////////
//break point
#ifdef _MSC_VER
#define TY_BREAK_POINT  __debugbreak();
#else
#define TY_BREAK_POINT  std::raise(SIGINT);
#endif


#define TY_FUNC_NOT_IMP TY_BREAK_POINT

#define D2F(value) (float)value

