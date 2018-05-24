#pragma once

#include "../common.h"

extern "C"
{

#define PLATFORM_EXIT_FORCED		1
#define PLATFORM_EXIT_PEACEFULL		0
#define PLATFORM_EXIT_ERROR			-1

struct EXPORT ApplicationInfo
{
	const char*	appName;
	const char*	appVersion;
};

#define WINDOW_BORDERLESS			0x1
#define WINDOW_VSYNC				0x2
#define WINDOW_FLAG_3				0x4
#define WINDOW_FLAG_4				0x8
#define WINDOW_FLAG_5				0x10
#define WINDOW_FLAG_6				0x20
#define WINDOW_FLAG_7				0x40
#define WINDOW_FLAG_8				0x80

struct EXPORT WindowInfo
{
	const char*	windowTitle;
	uint32		windowPosX;
	uint32		windowPosY;
	uint32		windowWidth;
	uint32		windowHeight;
	uint8		windowFlags;
};

#define MAX_MEMORY_BLOCK_SIZE		MEGABYTES(64)

struct INTERNAL MemoryBlock
{
	bool32	initialized;
	uint64	memorySize;
	void*	memoryBlock;
};

#define DLL		0
#define FUNC	0

typedef int32(*_TestPlatform)(int32 test);
typedef int32(*_LoadDLL)(const char* path);
typedef int32(*_LoadFunction)(const char* name);

static _TestPlatform	sTestPlatformFunc;
static _LoadDLL			sLoadDLLFunc;
static _LoadFunction	sLoadFunctionFunc;

#define TestPlatform(test)	sTestPlatformFunc(test)
#define LoadDLL(path)		sLoadDLLFunc(path)
#define LoadFunction(name)	sLoadFunctionFunc(name)

struct EXPORT PlatformFuncs
{
	_TestPlatform	funcTestPlatform;
	_LoadDLL		funcLoadDLL;
};

int32 GLOBAL EXPORT LoadPlatformFunctions(PlatformFuncs funcs);

}