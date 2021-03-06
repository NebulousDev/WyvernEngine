#include <iostream>
#include "win32Platform.h"
#include "win32Runtime.h"
#include "win32State.h"
#include "win32.h"

#define CORE_DLL_NAME "wyverngame.dll"

#define SET_STATE_MESSAGE		(WM_USER + 1)
#define SET_RUNTIME_MESSAGE		(WM_USER + 2)

LRESULT CALLBACK HandleEvents(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static Win32State* state = {};
	static Runtime* runtime = {};

	switch (uMsg)
	{
		case SET_STATE_MESSAGE:
		{
			state = (Win32State*)wParam;
			return 0;
		}

		case SET_RUNTIME_MESSAGE:
		{
			runtime = (Runtime*)wParam;
			return 0;
		}

		case WM_DESTROY:
		{
			state->running = false;
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

RESULT SetupApplication(Win32State* state)
{
	state->runtime = Win32CreateCoreRuntime(CORE_DLL_NAME);

	if (!state->runtime)
	{
		char buffer[512];
		sprintf(buffer, "Error: Failed to create core runtime. Is %s missing?", CORE_DLL_NAME);
		MessageBox(0, buffer, "Error", MB_OK);
		return FAILURE;
	}

	RESULT create = state->runtime->Create(&state->appInfo);

	if (!create)
	{
		MessageBox(0, "Error: Runtime creation returned a failure.", "Error", MB_OK);
		return FAILURE;
	}

	return SUCCESS;
}

RESULT CreateApplication(Win32State* state)
{
	state->wndClass.style			= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	state->wndClass.lpszClassName	= state->appInfo.appName;
	state->wndClass.hInstance		= state->instance;
	state->wndClass.lpfnWndProc		= &HandleEvents;

	if (!RegisterClass(&state->wndClass))
	{
		DWORD error = GetLastError();
		LPTSTR errorText = NULLPTR;
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&errorText, 0, NULL);

		char buffer[512];
		sprintf(buffer, "Error: Failed to create application. Unable to register WNDCLASS. \nError Message: %s", errorText);
		MessageBox(0, buffer, "Error", MB_OK);

		return FAILURE;
	}

	HandleEvents(0, SET_STATE_MESSAGE, (WPARAM)state, 0);
	HandleEvents(0, SET_RUNTIME_MESSAGE, (WPARAM)state->runtime, 0);

	return SUCCESS;
}

RESULT StartApplication(Win32State* state, Platform* platform)
{
	state->runtime->Start(&state->app, platform);
	state->running = true;

	MSG msg = {};
	while (state->running)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		state->runtime->Loop(&state->app);
	}

	return SUCCESS;
}

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR arguments, int show)
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);

	PlatformInfo platformInfo;
	platformInfo.platformName		= "Windows";
	platformInfo.platformVersion	= "Windows 10 Pro";

	Platform platform;
	Win32SetupPlatform(&platform, platformInfo);

	Win32State state;
	state.instance	= instance;
	state.arguments = arguments;
	state.runtime	= NULLPTR;
	state.wndClass	= {};
	state.appInfo	= {};
	state.app		= {};
	state.running	= false;

	InitWin32State(&state);

	RESULT result = SUCCESS;

	result = SetupApplication(&state);

	if (!result)
	{
		system("PAUSE");
		return 0;
	}

	std::cout << state.appInfo.appName << std::endl;
	std::cout << state.appInfo.appVersion << std::endl;
	std::cout << state.appInfo.appMemAllocSize << std::endl;

	result = CreateApplication(&state);
	result = StartApplication(&state, &platform);

	Win32FreeRuntime(state.runtime);

	FreeConsole();

	return 0;
}
