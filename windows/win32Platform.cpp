#include "win32Platform.h"
#include "win32Runtime.h"
#include "win32Window.h"

void Win32SetupPlatform(Platform* platform, PlatformInfo info)
{
	platform->platformInfo			= info;
	platform->fpCreateWindow		= Win32CreateWindow;
	platform->fpFreeWindow			= Win32FreeWindow;
	platform->fpSetWindowSize		= Win32SetWindowSize;
	platform->fpShowWindow			= Win32ShowWindow;
	platform->fpHideWindow			= Win32HideWindow;
	platform->fpCreateRuntime		= Win32CreateRuntime;
	platform->fpCreateCoreRuntime	= Win32CreateCoreRuntime;
	platform->fpFreeRuntime			= Win32FreeRuntime;
}
