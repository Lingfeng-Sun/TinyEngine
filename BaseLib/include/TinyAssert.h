//HoYoAi
//miHoYo Co., Ltd  All rights reserved
//Created by Haitian.lin  2023/6/6
#pragma once

//#if defined(NDEBUG) && !defined(HOYOAI_SHIPPING)
#if !defined(HOYOAI_SHIPPING)
#undef NDEBUG
#include <assert.h>

namespace HoYoAi
{
#define AiAssert(expression)   assert(expression)
}

#define NDEBUG
#else
#include <assert.h>

namespace HoYoAi
{
#define AiAssert(expression)   assert(expression)
}

#endif


