#pragma once
#include <platform\platform.h>
#include "win32.h"

struct Win32State
{
	HINSTANCE			instance;
	LPTSTR				arguments;
	WNDCLASS			wndClass;
	CoreRuntime*		runtime;
	ApplicationInfo		appInfo;
	Application			app;
	bool8				running;
};

void InitWin32State(Win32State* state);

const Win32State* GetWin32State();