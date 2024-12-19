//HoYoAi
//miHoYo Co., Ltd  All rights reserved
//Created by Haitian.lin  2023/6/6

#include "GlobalSingleton.h"
#include "SingletonObject.h"

namespace HoYoAi
{
static Global* sEngineGLobalInst{ nullptr };

void Global::InitGloablSinglton(Global* instance)
{
    AiAssert(instance);

    if (sEngineGLobalInst == nullptr)
    {
        sEngineGLobalInst = instance;
    }
    else
    {
        AiAssert(sEngineGLobalInst == instance);
    }
}

Global& Global::Instance()
{
    return *sEngineGLobalInst;
}

Global::~Global()
{
    for (auto& it : mSingletonObjects)
    {
        if (it.second.second)
        {
            it.second.first->Release();
        }
    }
    mSingletonObjects.clear();
}

}

