#pragma once

#include "../Common.h"

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

#define PLATFORM_USE_SDL			0

#if PLATFORM_USE_SDL == 1

#include "sdl\SDLPlatform.h"

#define _CreateApplication()		SDLCreateApplication()

#define _CreateWindow(info)			SDLCreateWindow(info)

#define _AllocPage(pages)			SDLAllocPage(pages)

#define _FreePages()				SDLFreePages()

#elif defined(_WIN32)

//#include "windows\Win32Platform.h"

#define _CreateApplication(info)	Win32CreateApplication(info)

#define _CreateWindow(info)			Win32CreateWindow(info)

#define _AllocPage(pages)			Win32AllocPage(pages)

#define _FreePages()				Win32FreePages()

#else
#error No platform layer defined!
#endif;

int32 GLOBAL EXPORT INLINE CreateApplication(ApplicationInfo info)
{
	return 0; // _CreateApplication(info);
}

int32 GLOBAL EXPORT INLINE CreateWindow(WindowInfo info)
{
	return 0; // _CreateWindow(info);
}

int32 GLOBAL EXPORT INLINE AllocPage(const uint32 pages)
{
	return 0; //  _AllocPage(pages);
}

int32 GLOBAL EXPORT INLINE FreePages()
{
	return 0; //  _FreePages();
}