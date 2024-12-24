#pragma once

#include "GlobalExport.h"
#include "TinyCommon.h"
#include <functional>
#include <utility>
#include <atomic>
#include <mutex>
#include "SingletonObject.h"

namespace ty
{
class SingletonObject
{
public:
    SingletonObject() = default;

    virtual void Release() = 0;

protected:
    virtual ~SingletonObject() = default;
    SingletonObject(SingletonObject&) = delete;
    SingletonObject& operator=(SingletonObject&) = delete;
};

using CreateSingletonObjectFunc = std::function<SingletonObject*(void*)>;

struct CreateSingletonParam
{
    CreateSingletonObjectFunc func;
    void* param{ nullptr };
};

class Global final
{
public:
    GlobalAPI static void Initialize();

    GlobalAPI static void Shutdown();

    template<typename T>
    static SingletonObject* RegisterSingletonObject(const CreateSingletonParam& createParam, bool autoRelease = true);

    template<typename T>
    static T* GetSingleton();
    
    //remove only
    template<typename T>
    static void RemoveSingletonObject();
    
    //remove and destroy 
    template<typename T>
    static void DestroySingletonObject();

private:
    Global() {};

    ~Global();

    Global(const Global&) = delete;
    Global& operator= (Global const&) = delete;

    GlobalAPI static Global& Instance();

    using SingletonObjectEntry = std::pair<SingletonObject*, bool>;
    TYHashMap<size_t, SingletonObjectEntry> mSingletonObjects;
    std::atomic<int32_t> mAccessingCount{ 0 };
    std::mutex mMutex;
};

template<typename T>
SingletonObject* Global::RegisterSingletonObject(const CreateSingletonParam& createParam, bool autoRelease)
{
    size_t key = typeid(T).hash_code(); 
   
    std::lock_guard<std::mutex> lock(Instance().mMutex);
    auto& singletonObjects = Instance().mSingletonObjects;
    auto it = singletonObjects.find(key);
    if (it != singletonObjects.end())
    {
        return it->second.first;
    }
    else
    {
        SingletonObject* globalObject = createParam.func(createParam.param);
        singletonObjects.emplace(key, std::make_pair(globalObject, autoRelease));
        return globalObject;
    }
}

template<typename T>
T* Global::GetSingleton()
{
    size_t key = typeid(T).hash_code(); 
    
    std::lock_guard<std::mutex> lock(Instance().mMutex);
    auto& singletonObjects = Instance().mSingletonObjects;
    auto it = singletonObjects.find(key);
    if (it != singletonObjects.end())
    {
        return it->second.first->Cast<T>();
    }
    return nullptr;
}

template<typename T>
void Global::RemoveSingletonObject()
{
    size_t key = typeid(T).hash_code(); 
    
    std::lock_guard<std::mutex> lock(Instance().mMutex);
    auto& singletonObjects = Instance().mSingletonObjects;
    auto it = singletonObjects.find(key);
    if (it != singletonObjects.end())
    {
        singletonObjects.erase(it);
    }
}

template<typename T>
void Global::DestroySingletonObject()
{
    size_t key = typeid(T).hash_code();

    std::lock_guard<std::mutex> lock(Instance().mMutex);
    auto& singletonObjects = Instance().mSingletonObjects;
    auto it = singletonObjects.find(key);
    if (it != singletonObjects.end())
    {
        it->second.first->Release();
        singletonObjects.erase(it);
    }
}

}
