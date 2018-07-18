#pragma once
#include "../common.h"

#define MAX_WINDOWS		64

#define WINDOW_SHOWN		0x1
#define WINDOW_CENTERED		0x2
#define WINDOW_FULLSCREEN	0x3
#define WINDOW_BORDERLESS	0x4

#define INVALID_HANDLE	-1;

struct WindowInfo
{
	const char*		title;
	uint32			width;
	uint32			height;
	uint32			posX;
	uint32			posY;
	BITS32			flags;
};

struct Window
{
	uint32			id;
	uint32			next;
	WYVPTRHANDLE	instance;
	const char*		title;
	uint32			width;
	uint32			height;
	uint32			posX;
	uint32			posY;
	BITS32			flags;
	bool8			valid;
};

typedef WYVHANDLE WindowHandle;

bool8				ValidateHandle(WindowHandle window);

const WindowHandle	CreateWindow(const WindowInfo info);

RESULT				FreeWindow(WindowHandle* window);

const Window*		GetWindow(WindowHandle window);

const WYVPTRHANDLE	GetWindowInstance(WindowHandle window);

RESULT				GetWindowSize(const WindowHandle window, uint32* width, uint32* height);

RESULT				SetWindowSize(const WindowHandle window, uint32 width, uint32 height);

RESULT				ShowWindow(const WindowHandle window);

RESULT				HideWindow(const WindowHandle window);
