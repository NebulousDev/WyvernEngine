#pragma once

#include "../common.h"

extern "C"
{

/*=================================================================
|	RETURN CODES                                                  |
=================================================================*/

#define PLATFORM_EXIT_FORCED		1
#define PLATFORM_EXIT_PEACEFULL		0
#define PLATFORM_EXIT_ERROR			-1

/*=================================================================
|	APPLICATION                                                   |
=================================================================*/

struct EXPORT ApplicationInfo
{
	const char*	appName;
	const char*	appVersion;
};

/*=================================================================
|	WINDOW                                                        |
=================================================================*/

#define WINDOW_BORDERLESS		0x1
#define WINDOW_VSYNC			0x2
#define WINDOW_FLAG_3			0x4
#define WINDOW_FLAG_4			0x8
#define WINDOW_FLAG_5			0x10
#define WINDOW_FLAG_6			0x20
#define WINDOW_FLAG_7			0x40
#define WINDOW_FLAG_8			0x80

struct EXPORT WindowInfo
{
	const char*	windowTitle;
	uint32		windowPosX;
	uint32		windowPosY;
	uint32		windowWidth;
	uint32		windowHeight;
	uint8		windowFlags;
};

/*=================================================================
|	MEMORY                                                        |
=================================================================*/

#define MAX_MEMORY_BLOCK_SIZE MEGABYTES(64)

struct INTERNAL MemoryBlock
{
	bool32	initialized;
	uint64	memorySize;
	void*	memoryBlock;
};

/*=================================================================
|	FUNCTIONS                                                     |
=================================================================*/

typedef int32				DLLHandle;
typedef void*				FuncHandle;

typedef DLLHandle			(*_LoadDLL)(const char* path);
typedef FuncHandle			(*_LoadFunction)(const DLLHandle, const char* name);

static _LoadDLL				sLoadDLLFunc;
static _LoadFunction		sLoadFunctionFunc;

#define LoadDLL(path)		sLoadDLLFunc(path)
#define LoadFunction(name)	sLoadFunctionFunc(name)

struct EXPORT PlatformFuncs
{
	_LoadDLL		funcLoadDLL;
	_LoadFunction	funcLoadFunction;
};

int32 GLOBAL EXPORT LoadPlatformFunctions(PlatformFuncs funcs);

FuncHandle GLOBAL EXPORT GetEnteranceFunc();

}