
#include "Global.h"
#include "TinyNewDelete.h"

namespace ty
{
static Global* sEngineGLobalInst{ nullptr };

void Global::Initialize()
{
    mi_version();

    if (!sEngineGLobalInst)
        sEngineGLobalInst = new Global();
}

void Global::Shutdown()
{
    if (sEngineGLobalInst)
    {
        delete sEngineGLobalInst;
        sEngineGLobalInst = nullptr;
    }
}

Global& Global::Instance()
{
    return *sEngineGLobalInst;
}

Global::~Global()
{
    if(sEngineGLobalInst)
    { 
        for (auto& it : Instance().mSingletonObjects)
        {
            if (it.second.second)
            {
                it.second.first->Release();
            }
        }
        mSingletonObjects.clear();
    }
    delete sEngineGLobalInst;
}


}

