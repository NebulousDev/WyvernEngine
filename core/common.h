#pragma once
#include "types.h"

#define WYVERN_CORE_API		__declspec(dllexport)
#define WYVERN_DLL_API		extern "C" __declspec(dllexport)

#define KILOBYTES(size)		1000 * size
#define MEGABYTES(size)		1000 * KILOBYTES(size)
#define GIGABYTES(size)		1000 * MEGABYTES(size)

typedef uint32 result;
#define RESULT result

#define SUCCESS 0x1
#define FAILURE 0x0

#define NULLPTR nullptr

#define INLINE	__inline
