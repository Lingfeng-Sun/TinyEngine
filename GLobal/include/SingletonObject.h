//HoYoAi
//miHoYo Co., Ltd  All rights reserved
//Created by Haitian.lin  2023/6/6
#pragma once

#include "BaseLibExport.h"

namespace HoYoAi
{

class AiBaseLibAPI SingletonObject
{
public:
    SingletonObject() = default;
    virtual ~SingletonObject() = default;
    virtual void Release() = 0;

private:
    SingletonObject(SingletonObject&) = delete;
    SingletonObject& operator=(SingletonObject&) = delete;
};

}
