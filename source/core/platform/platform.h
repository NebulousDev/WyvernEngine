#pragma once

#include "../common.h"
#include "../graphics/graphics.h"

//TODO: Make compiler flags
/////////////////////////////////////////
#define GFXAPI_OPENGL_ENABLED
#define GFXAPI_VULKAN_ENABLED
#define GFXAPI_DIRECT3D_9_ENABLED
#define GFXAPI_DIRECT3D_11_ENABLED
#define GFXAPI_DIRECT3D_12_ENABLED
/////////////////////////////////////////

/*=================================================================
|	RETURN CODES                                                  |
=================================================================*/

#define PLATFORM_EXIT_FORCED		1
#define PLATFORM_EXIT_PEACEFULL		0
#define PLATFORM_EXIT_ERROR			-1

/*=================================================================
|	APPLICATION                                                   |
=================================================================*/

EXPORT_STRUCT ApplicationInfo
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

EXPORT_STRUCT WindowInfo
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

typedef int32						DLLHandle;

typedef RESULT						(*fLoadDLL)(const char* path);
typedef RESULT						(*fLoadFunction)(const DLLHandle, const char* name);

typedef void*						(*fAllocateBytes)(const uint32 size);

#if defined(GFXAPI_OPENGL_ENABLED)
typedef RESULT						(*fOpenGLCreateContext)();
typedef RESULT						(*fOpenGLMakeContextCurrent)();
#endif

extern fLoadDLL						sLoadDLLFunc;
extern fLoadFunction				sLoadFunctionFunc;

extern fAllocateBytes				sAllocateBytesFunc;

#if defined(GFXAPI_OPENGL_ENABLED)
extern fOpenGLCreateContext			sOpenGLCreateContextFunc;
extern fOpenGLMakeContextCurrent	sOpenGLMakeContextCurrentFunc;
#endif

#define LoadDLL(path)				sLoadDLLFunc(path)
#define LoadFunction(name)			sLoadFunctionFunc(name)

#define AllocateBytes(size)			sAllocateBytesFunc(size)

#if defined(GFXAPI_OPENGL_ENABLED)
#define OpenGLCreateContext()		sOpenGLCreateContextFunc()
#define OpenGLMakeContextCurrent()	sOpenGLMakeContextCurrentFunc()
#endif

EXPORT_STRUCT PlatformFuncs
{
	fLoadDLL					funcLoadDLL;
	fLoadFunction				funcLoadFunction;

	fAllocateBytes				funcAllocateBytes;

#if defined(GFXAPI_OPENGL_ENABLED)
	fOpenGLCreateContext		funcOpenGLCreateContext;
	fOpenGLMakeContextCurrent	funcOpenGLMakeContextCurrent;
#endif

};
 
EXPORT int32 LoadPlatformFunctions(PlatformFuncs funcs);