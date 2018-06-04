#pragma once

#include "../common.h"

class StackAllocator
{
private:
	ubyte8* mStart;
	ubyte8* mEnd;

	ubyte8* mNext;

	uint32 mSize;
	uint32 mUsed;
	uint32 mRemaining;

public:

	StackAllocator(const uint32 size);

	template<typename Object>
	INLINE Object* Allocate();

	template<typename Object>
	INLINE Object* AllocateArray(const uint32 num);

	INLINE void Free(void* data);

	INLINE void FreeAll();

	INLINE void Release();
};

class DoubleAllocator
{

};

class PoolAllocator
{

};