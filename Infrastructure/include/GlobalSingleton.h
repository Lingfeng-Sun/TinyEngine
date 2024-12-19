//HoYoAi
//miHoYo Co., Ltd  All rights reserved
//Created by Haitian.lin  2023/6/6
#pragma once

#include "BaseLibExport.h"
#include "BaseLibDefine.h"
#include "SingletonObject.h"
#include "AiAssert.h"
#include "AiMap.h"
#include "TypeCast.h"

namespace HoYoAi
{
class SingletonObject;

class Global
{
public:
    AiBaseLibAPI static void InitGloablSinglton(Global* instance);

    AiBaseLibAPI static Global& Instance();

    AiBaseLibAPI Global() {};

    AiBaseLibAPI ~Global();

    template<typename T>
    void AddGlobalObject(SingletonObject* globalObject, bool autoRelease = true);

    template<typename T>
    T* GetGlobalObject();
    
    //remove only
    template<typename T>
    void RemoveGlobalObject();
    
    //remove and destroy 
    template<typename T>
    void DestroyGlobalObject();

private:
    Global(const Global&) = delete;
    Global& operator= (Global const&) = delete;

    using SingletonObjectEntry = std::pair<SingletonObject*, bool>;
    AiHashMap<size_t, SingletonObjectEntry> mSingletonObjects;
};

template<typename T>
AI_INLINE void Global::AddGlobalObject(SingletonObject* globalObject, bool autoRelease)
{
    if (!globalObject)
        return;

    size_t key = typeid(T).hash_code(); 
    AiAssert(mSingletonObjects.find(key) == mSingletonObjects.end());
    mSingletonObjects.emplace(key, std::make_pair(globalObject, autoRelease));
}

template<typename T>
AI_INLINE T* Global::GetGlobalObject()
{
    size_t key = typeid(T).hash_code();
    auto it = mSingletonObjects.find(key);
    if (it != mSingletonObjects.end())
    {
        return TypeCast<T*>(it->second.first);
    }
    return nullptr;
}

template<typename T>
AI_INLINE void Global::RemoveGlobalObject()
{
    size_t key = typeid(T).hash_code();
    auto it = mSingletonObjects.find(key);
    if (it != mSingletonObjects.end())
    {
        mSingletonObjects.erase(it);
    }
}

template<typename T>
AI_INLINE void Global::DestroyGlobalObject()
{
    size_t key = typeid(T).hash_code();
    auto it = mSingletonObjects.find(key);
    if (it != mSingletonObjects.end())
    {
        it->second.first->Release();
        mSingletonObjects.erase(it);
    }
}

#define AppGlobal Global::Instance()


}
