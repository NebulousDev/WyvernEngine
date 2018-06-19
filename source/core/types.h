#pragma once

#define GLOBAL					
#define INTERNAL				
#define EXTERNAL				
#define INLINE					__inline
#define EXPORT					extern "C" __declspec(dllexport)
#define EXPORT_STRUCT			extern "C" struct __declspec(dllexport)

#ifndef NULL
#define NULL					0x00000000
#endif

enum WyvernResult
{
	WYVERN_ERROR	= 0,
	WYVERN_SUCCESS	= 1
};

#define RESULT					WyvernResult

#if defined(_MSVC_LANG)

typedef	bool					bool32;

typedef __int8					byte8;
typedef	__int8					int8;
typedef __int16					int16;
typedef __int32					int32;
typedef __int64					int64;

typedef unsigned __int8			ubyte8;
typedef	unsigned __int8			uint8;
typedef	unsigned __int16		uint16;
typedef unsigned __int32		uint32;
typedef unsigned __int64		uint64;

typedef float					float32;

#endif

#include "string.h"