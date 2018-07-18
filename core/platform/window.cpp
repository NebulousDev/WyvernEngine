#include "window.h"
#include "platform.h"
#include <iostream>

static Window			sWindows[MAX_WINDOWS] = {};
static uint32			sNextWindow = 0;
static bool8			sInitialized = false;

bool8 ValidateHandle(WindowHandle handle)
{
	return handle > -1 && handle < 65 && sWindows[handle].valid;
}

const WindowHandle CreateWindow(const WindowInfo info)
{
	if (!sInitialized)
	{
		for (int i = 0; i < MAX_WINDOWS; i++)
		{
			sWindows[i].id = i;
			sWindows[i].next = i + 1;
		}

		sInitialized = true;
	}

	if (sNextWindow > 64)
	{
		//TODO: throw error?
		return INVALID_HANDLE;
	}

	WindowHandle handle = sNextWindow;

	if (!GetPlatform()->fpCreateWindow(&sWindows[handle], info))
	{
		//TODO: throw error?
		return INVALID_HANDLE;
	}

	sNextWindow = sWindows[handle].next;
	Window* window = &sWindows[handle];

	return handle;
}

RESULT FreeWindow(WindowHandle* handle)
{
	if (handle != NULLPTR && ValidateHandle(*handle))
	{
		if (GetPlatform()->fpFreeWindow(&sWindows[*handle]))
		{
			sWindows[*handle].next = sNextWindow;
			sNextWindow = sWindows[*handle].id;
			*handle = INVALID_HANDLE;
			return SUCCESS;
		}
	}

	return FAILURE;
}

const Window* GetWindow(WindowHandle window)
{
	if (ValidateHandle(window))
		return &sWindows[window];

	return NULLPTR;
}

const WYVPTRHANDLE GetWindowInstance(WindowHandle window)
{
	if (ValidateHandle(window))
		return sWindows[window].instance;

	return NULLPTR;
}

RESULT GetWindowSize(const WindowHandle window, uint32* width, uint32* height)
{
	if (ValidateHandle(window))
	{
		*width = sWindows[window].width;
		*height = sWindows[window].height;
		return SUCCESS;
	}

	return FAILURE;
}

RESULT SetWindowSize(const WindowHandle window, uint32 width, uint32 height)
{
	if (ValidateHandle(window))
	{
		if (GetPlatform()->fpSetWindowSize(&sWindows[window], width, height))
			return SUCCESS;
	}
	
	return FAILURE;
}

RESULT ShowWindow(const WindowHandle window)
{
	if (ValidateHandle(window))
	{
		if (GetPlatform()->fpShowWindow(&sWindows[window]))
		{
			sWindows[window].flags |= WINDOW_SHOWN;
			return SUCCESS;
		}
	}

	return FAILURE;
}

RESULT HideWindow(const WindowHandle window)
{
	if (ValidateHandle(window))
	{
		if (GetPlatform()->fpShowWindow(&sWindows[window]))
		{
			sWindows[window].flags &= ~WINDOW_SHOWN;
			return SUCCESS;
		}
	}
	
	return FAILURE;
}