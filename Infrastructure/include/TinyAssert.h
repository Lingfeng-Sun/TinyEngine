
#pragma once
#if !defined(HOYOAI_SHIPPING)
#undef NDEBUG
#include <assert.h>

namespace tiny
{
#define TinyAssert(expression)   assert(expression)

#define TinyAssertSlow(expression)   assert(expression)
}

#define NDEBUG
#else
#include <assert.h>
namespace tiny
{
#define TinyAssert(expression)   assert(expression)

#define TinyAssert(expression)   assert(expression)
}

#endif


