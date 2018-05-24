#include "Memory.h"

#include "../platform/platform.h"

INLINE MemoryBlock GLOBAL CreateMemoryBlock(const int pages)
{
	// MemoryBlock block = {};
	// block.memorySize	= pages * PAGE_SIZE;
	// block.memoryBlock	= AllocPage(pages);
	// 
	// return block;
}

INLINE void* GLOBAL Alloc(MemoryBlock* memory, const uint32 size)
{

}