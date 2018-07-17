#include "win32Window.h"
#include "win32State.h"
#include "win32.h"

RESULT Win32CreateWindow(Window* window, const WindowInfo info)
{
	if (window == NULLPTR)
	{
		//TODO: throw error?
		return FAILURE;
	}

	const Win32State* state = GetWin32State();
	const char* className = state->wndClass.lpszClassName;

	uint32 posX		= info.posX;
	uint32 posY		= info.posY;
	uint32 width	= info.width;
	uint32 height	= info.height;

	uint32 flags	= WS_OVERLAPPEDWINDOW;

	if (info.flags & WINDOW_CENTERED)
	{
		// Center window
	}

	if (info.flags & WINDOW_FULLSCREEN)
	{
		// Center window
	}

	if (info.flags & WINDOW_BORDERLESS)
	{
		// Center window
	}

	HWND winHandle = CreateWindow
	(
		state->wndClass.lpszClassName, info.title,
		flags, posX, posY, width, height,
		NULL, NULL, state->instance, NULL
	);

	if (!window)
	{
		//TODO: throw error?
		return FAILURE;
	}

	if (info.flags & WINDOW_SHOWN)
	{
		if (!ShowWindow(winHandle, true))
		{
			//TODO: throw error?
			return FAILURE;
		}
	}

	window->instance	= (WYVPTRHANDLE)winHandle;
	window->title		= info.title;
	window->width		= width;
	window->height		= height;
	window->posX		= posX;
	window->posY		= posY;
	window->flags		= info.flags;
	window->valid		= true;

	return SUCCESS;
}

RESULT Win32FreeWindow(Window* window)
{
	if (DestroyWindow((HWND)window->instance))
	{
		window->valid = false;
		return SUCCESS;
	}

	return FAILURE;
}

RESULT Win32SetWindowSize(Window* window, uint32 width, uint32 height)
{
	return SUCCESS;
}

RESULT Win32ShowWindow(Window* window)
{
	if (!ShowWindow((HWND)window->instance, true))
	{
		//TODO: throw error?
		return FAILURE;
	}

	window->flags |= WINDOW_SHOWN;

	return SUCCESS;
}

RESULT Win32HideWindow(Window* window)
{
	if (!ShowWindow((HWND)window->instance, false))
	{
		//TODO: throw error?
		return FAILURE;
	}

	window->flags &= ~WINDOW_SHOWN;

	return SUCCESS;
}
