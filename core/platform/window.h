#pragma once
#include "../common.h"

#define MAX_WINDOWS			64

#define WINDOW_SHOWN		0x1
#define WINDOW_CENTERED		0x2
#define WINDOW_FULLSCREEN	0x3
#define WINDOW_BORDERLESS	0x4

struct WYVERN_CORE_API WindowInfo
{
	const STRING	title;
	uint32			width;
	uint32			height;
	uint32			posX;
	uint32			posY;
	BITS32			flags;
};

struct WYVERN_CORE_API Window
{
	uint32			id;
	uint32			next;
	WYVPTRHANDLE	hInstance;
	const STRING	title;
	uint32			width;
	uint32			height;
	uint32			posX;
	uint32			posY;
	BITS32			flags;
	bool8			valid;
};

typedef WYVHANDLE WindowHandle;
#define WYVHWINDOW WindowHandle;

WYVERN_CORE_API
bool8				ValidateWindowHandle(WindowHandle window);
WYVERN_CORE_API
const WindowHandle	CreateWindow(const WindowInfo info);
WYVERN_CORE_API
RESULT				FreeWindow(WindowHandle* pWindow);
WYVERN_CORE_API
const Window*		GetWindow(WindowHandle window);
WYVERN_CORE_API
const WYVPTRHANDLE	GetWindowInstance(WindowHandle window);
WYVERN_CORE_API
RESULT				GetWindowSize(const WindowHandle window, uint32* pWidth, uint32* pHeight);
WYVERN_CORE_API
RESULT				SetWindowSize(const WindowHandle window, uint32 width, uint32 height);
WYVERN_CORE_API
RESULT				ShowWindow(const WindowHandle window);
WYVERN_CORE_API
RESULT				HideWindow(const WindowHandle window);
