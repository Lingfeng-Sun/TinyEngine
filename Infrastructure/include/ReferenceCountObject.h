
#pragma once

#include <stdint.h>
#include <atomic>
#include "TinyCommon.h"

namespace HoYoAi
{

class ReferenceCountObject
{
public:
	virtual ~ReferenceCountObject() { TinyAssert(mRefCount == 0); }

    TY_DEBUGNOINLINE void IncreaseRefCount()
    { 
        mRefCount++; 
    }

    TY_DEBUGNOINLINE void DecreaseRefCount()
	{ 
		mRefCount--; 
		if (mRefCount == 0)
			OnZeroReference();
	}

    TY_INLINE int32_t GetRefCount() { return mRefCount; }

    TY_DEBUGNOINLINE void IncreaseRefCount() const { mRefCount++; }

    TY_DEBUGNOINLINE void DecreaseRefCount() const
	{
		mRefCount--;
		if (mRefCount == 0)
			OnZeroReference();
	}

    TY_INLINE int32_t GetRefCount() const { return mRefCount; }

protected:
    virtual void OnZeroReference() { delete this; }

	virtual void OnZeroReference() const { delete this; }

private:
	ReferenceCountObject(ReferenceCountObject const&) = delete;

	ReferenceCountObject& operator=(ReferenceCountObject const&) = delete;

protected:
	ReferenceCountObject() = default;

	mutable std::atomic<int32_t> mRefCount{ 0 };
};

}
