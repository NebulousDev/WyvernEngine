#pragma once

#define WIN32_LEAN_AND_MEAN		1
#define NOCOMM					1

#include <Windows.h>

#define CORE_DLL_NAME			"wyverncore.dll"

#define GLOBAL					
#define INTERNAL				
#define EXTERNAL				
#define INLINE					__inline
#define EXPORT					extern "C" __declspec(dllexport)
#define EXPORT_STRUCT			extern "C" struct __declspec(dllexport)

#ifndef NULL
#define NULL					0x00000000
#endif // !NULL

enum WyvernResult
{
	WYVERN_ERROR = 0,
	WYVERN_SUCCESS = 1
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

#define KILOBYTES(num)			(1024 * (value))
#define MEGABYTES(num)			(1024 * KILOBYTES(num))
#define GIGABYTES(num)			(1024L * MEGABYTES(num))
#define TERABYTES(num)			(1024L * GIGABYTES(num))

typedef HDC		GraphicsDevice;
typedef HGLRC	GraphicsContext;

struct ApplicationInfo
{
	const char*	appName;
	const char*	appVersion;
};

struct WindowInfo
{
	const char*	windowTitle;
	uint32		windowPosX;
	uint32		windowPosY;
	uint32		windowWidth;
	uint32		windowHeight;
	uint8		windowFlags;
};

struct Win32State
{
	HINSTANCE		instance;
	WNDCLASS		windClass;
	HWND			window;
	GraphicsContext	gfxContext;
	GraphicsDevice	gfxDevice;
	PWSTR			arguments;
	uint32			show;
	bool32			running;
};

#define STARTUP_STATE_MESSAGE	(WM_USER + 1)
#define NEW_RUNTIME_MESSAGE		(WM_USER + 2)