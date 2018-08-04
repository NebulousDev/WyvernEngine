#include "window.h"
#include "platform.h"
#include <iostream>

static Window			sWindows[MAX_WINDOWS] = {};
static uint32			sNextWindow = 0;
static bool8			sInitialized = false;

bool8 ValidateWindowHandle(WindowHandle hHandle)
{
	return hHandle > -1 && hHandle < (MAX_WINDOWS + 1) && sWindows[hHandle].valid;
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

	if (sNextWindow > MAX_WINDOWS)
	{
		//TODO: throw error?
		return INVALID_HANDLE;
	}

	WindowHandle hWindow = sNextWindow;

	if (!GetPlatform()->fpCreateWindow(&sWindows[hWindow], info))
	{
		//TODO: throw error?
		return INVALID_HANDLE;
	}

	sNextWindow = sWindows[hWindow].next;
	Window* pWindow = &sWindows[hWindow];

	return hWindow;
}

RESULT FreeWindow(WindowHandle* phWindow)
{
	if (phWindow != NULLPTR && ValidateWindowHandle(*phWindow))
	{
		if (GetPlatform()->fpFreeWindow(&sWindows[*phWindow]))
		{
			sWindows[*phWindow].next = sNextWindow;
			sNextWindow = sWindows[*phWindow].id;
			*phWindow = INVALID_HANDLE;
			return SUCCESS;
		}
	}

	return FAILURE;
}

const Window* GetWindow(WindowHandle hWindow)
{
	if (ValidateWindowHandle(hWindow))
		return &sWindows[hWindow];

	return NULLPTR;
}

const WYVPTRHANDLE GetWindowInstance(WindowHandle hWindow)
{
	if (ValidateWindowHandle(hWindow))
		return sWindows[hWindow].hInstance;

	return NULLPTR;
}

RESULT GetWindowSize(const WindowHandle hWindow, uint32* pWidth, uint32* pHeight)
{
	if (ValidateWindowHandle(hWindow))
	{
		*pWidth = sWindows[hWindow].width;
		*pHeight = sWindows[hWindow].height;
		return SUCCESS;
	}

	return FAILURE;
}

RESULT SetWindowSize(const WindowHandle hWindow, uint32 width, uint32 height)
{
	if (ValidateWindowHandle(hWindow))
	{
		if (GetPlatform()->fpSetWindowSize(&sWindows[hWindow], width, height))
			return SUCCESS;
	}
	
	return FAILURE;
}

RESULT ShowWindow(const WindowHandle hWindow)
{
	if (ValidateWindowHandle(hWindow))
	{
		if (GetPlatform()->fpShowWindow(&sWindows[hWindow]))
		{
			sWindows[hWindow].flags |= WINDOW_SHOWN;
			return SUCCESS;
		}
	}

	return FAILURE;
}

RESULT HideWindow(const WindowHandle hWindow)
{
	if (ValidateWindowHandle(hWindow))
	{
		if (GetPlatform()->fpShowWindow(&sWindows[hWindow]))
		{
			sWindows[hWindow].flags &= ~WINDOW_SHOWN;
			return SUCCESS;
		}
	}
	
	return FAILURE;
}