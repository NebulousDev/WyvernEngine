#pragma once

#define GLOBAL					
#define INTERNAL
#define EXTERNAL				
#define INLINE					__inline
#define EXPORT					__declspec(dllexport)
#define NULL					0x00000000

#define WYVERN_SUCCESS			1
#define WYVERN_ERROR			0

#define TYPE_STRING				char*
typedef TYPE_STRING				string;

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

#define KILOBYTES(num)			(1024 * (value))
#define MEGABYTES(num)			(1024 * KILOBYTES(num))
#define GIGABYTES(num)			(1024L * MEGABYTES(num))
#define TERABYTES(num)			(1024L * GIGABYTES(num))