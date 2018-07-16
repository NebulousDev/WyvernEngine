#pragma once

#define RESULT uint8

#define SUCCESS 0x1
#define FAILURE 0x0

#define NULLPTR 0

#define INLINE	__forceinline

typedef __int8					int8;
typedef __int16					int16;
typedef __int32					int32;
typedef __int64					int64;

typedef unsigned __int8			uint8;
typedef unsigned __int16		uint16;
typedef unsigned __int32		uint32;
typedef unsigned __int64		uint64;

typedef float					f32;
typedef double					d64;

typedef uint8					bool8;

struct ApplicationInfo
{
	const char*		appName;
	const char*		appVersion;
	uint64			appMemAllocSize;
};

struct Application
{

};

struct Platform
{

};