#include "Memory.h"

#include "../platform/platform.h"

#include <malloc.h>

StackAllocator::StackAllocator(const uint32 size)
	: mSize(size), mUsed(0), mRemaining(size)
{
	//TODO: Replace malloc with custom platform allocation
	mStart = (ubyte8*)malloc(size);
	mEnd = mStart + size;

	mNext = mStart;
}

template<typename Object>
Object* StackAllocator::Allocate()
{
	uint32 objSize = sizeof(Object);
	if (objSize < mRemaining)
	{
		// TODO: Add assertions
		void* data = mNext;

		mNext += objSize;
		mUsed += objSize;
		mRemaining -= objSize;

		return (Object*)data;
	}
	
	return NULL;
}

template<typename Object>
Object* StackAllocator::AllocateArray(const uint32 num)
{
	uint32 objSize = sizeof(Object) * num;
	if (objSize < mRemaining)
	{
		// TODO: Add assertions
		void* data = mNext;

		mNext += objSize;
		mUsed += objSize;
		mRemaining -= objSize;

		return (Object*)data;
	}

	return NULL;
}

void StackAllocator::Free(uint8* data)
{
	if (data >= mStart && data <= mEnd)
	{
		// TODO: Add assertions
		uint32 sizeFreed = (uint32)mNext - (uint32)data;
		
		mNext = (ubyte8*)data;
		mRemaining += sizeFreed;
		mUsed -= sizeFreed;
	}
}

void StackAllocator::FreeAll()
{
	Free(mStart);
}

void StackAllocator::Release()
{
	free(mStart);
}