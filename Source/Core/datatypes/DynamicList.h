#pragma once
#include "../Common.h"
#include "../memory/Memory.h"
#include "DataType.h"

#define DYNAMIC_LIST_MAX_SIZE 4096

template<typename Item>
class EXPORT DynamicList : DataType
{
private:

	int32				mSize;
	Item*				mData;

	bool INLINE DeleteData()
	{

	}

public:

	DynamicList() : mSize(0), mData(NULL) { }

	DynamicList(const uint32 size, const bool zero = true) : mSize(size)
	{
		if (mUseAllocator)
		{

		}
	}

	DynamicList(const uint32 size, Item* data)
	{

	}

	bool INLINE Add(Item item)
	{

	}

	bool INLINE Remove(const uint32 index)
	{

	}

	bool INLINE Remove(Item* ptr)
	{
		if(ptr > 0 && ptr < mSize)

	}

	Item* INLINE At(const uint32 index)
	{
		if (index >= 0 && index <= DYNAMIC_LIST_MAX_SIZE)
			return mData[index];
	}

	Item* INLINE Data()
	{
		return mData;
	}

	const uint32 INLINE Size()
	{
		return mSize;
	}
};