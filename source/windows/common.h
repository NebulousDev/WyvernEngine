#pragma once

#include "header.h"
#include "context.h"
#include "types.h"
#include "platform.h"

#define CORE_DLL_NAME			"wyverncore.dll"

#define STARTUP_STATE_MESSAGE	(WM_USER + 1)
#define NEW_RUNTIME_MESSAGE		(WM_USER + 2)

#define KILOBYTES(num)			(1024 * (value))
#define MEGABYTES(num)			(1024 * KILOBYTES(num))
#define GIGABYTES(num)			(1024L * MEGABYTES(num))
#define TERABYTES(num)			(1024L * GIGABYTES(num))

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

	//TODO: Should app and gfx be in the win32state?
	PlatformApplication*	platformApp;
	PlatformGraphics*		platformGfx;
};
