
#include "win32Platform.h"
#include "win32OpenGL.h"
#include <iostream>

#include <GL\glew.h>

LRESULT CALLBACK Win32WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC deviceContext = GetDC(hwnd);
	GLContext glContext = NULL;

	switch (uMsg)
	{
		case WM_CREATE:
		{
			glContext = Win32CreateOpenGLContext(deviceContext);

			if (!glContext)
			{
				Win32DebugConsolePrint("Failed to create glContext!");
			}

			if (!Win32InitOpenGL())
			{
				Win32DebugConsolePrint("Failed to init GLEW!");
			}

			return 0;
		}

		case WM_DESTROY:
		{
			Win32DeleteOpenGLContext(glContext);
			Win32ExitApplication(PLATFORM_EXIT_PEACEFULL);
			return 0;
		}

		case WM_PAINT:
		{
			return 0;
		}

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int32 GLOBAL Win32CreateApplication(HINSTANCE instance, ApplicationInfo info, WNDCLASS* windClass)
{
	windClass->style				= CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	windClass->lpszClassName		= info.appName;
	windClass->hInstance			= instance;
	windClass->lpfnWndProc			= Win32WindowCallback;

	if (!RegisterClass(windClass))
	{
		return WYVERN_ERROR;
	}

	return WYVERN_SUCCESS;
}

int32 GLOBAL win32CreateWindow(HINSTANCE instance, WNDCLASS windClass, WindowInfo info, HWND* wind)
{
	*wind = CreateWindowEx
	(
		0,
		windClass.lpszClassName,
		info.windowTitle,
		WS_OVERLAPPEDWINDOW,
		info.windowPosX, info.windowPosY,
		info.windowWidth, info.windowHeight,
		NULL, NULL, instance, NULL
	);

	if(*wind == NULL)
	{
		return WYVERN_ERROR;
	}

	return WYVERN_SUCCESS;
}

int32 GLOBAL Win32AllocPage(const uint32 pages, uint32* bytes, void* data)
{
	//data = VirtualAlloc(data, )
	return WYVERN_SUCCESS;
}

int32 GLOBAL Win32FreePages()
{
	return WYVERN_SUCCESS;
}

int32 GLOBAL Win32LoadDLL(const char* path)
{
	return WYVERN_SUCCESS;
}

int32 GLOBAL Win32ExitApplication(int32 code)
{
	PostQuitMessage(code);
	return code;
}

int32 GLOBAL Win32ForceKillApplication(int32 code)
{
	// TODO: implement ForceKillApplication
	return code;
}

void GLOBAL Win32DebugConsolePrint(const char* text)
{
	//DWORD charsWritten;
	//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), text, strlen(text), &charsWritten, NULL);
	OutputDebugString(text);
}

/////////////////////////////////////////////////////////////////////////////////////////

typedef int32 (*_LoadPlatformFunctions)(PlatformFuncs funcs);
static _LoadPlatformFunctions sLoadPlatformFunctionsFunc;
#define LoadPlatformFunctions(funcs) sLoadPlatformFunctionsFunc(funcs)

int32 GLOBAL Win32LoadWyvernCore()
{
	HMODULE wyvernCoreDll = LoadLibrary("wyverncore.dll");

	sLoadPlatformFunctionsFunc = (_LoadPlatformFunctions)GetProcAddress(wyvernCoreDll, "LoadPlatformFunctions");

	PlatformFuncs funcs = {};

	LoadPlatformFunctions(funcs);

	return WYVERN_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////////////

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	WNDCLASS	windClass	= {};
	HWND		wind		= NULL;

	ApplicationInfo appInfo = {};
	appInfo.appName			= "WyvernGame";
	appInfo.appVersion		= "1.0.0";

	WindowInfo windInfo = {};
	windInfo.windowTitle	= "Wyvern Game";
	windInfo.windowPosX		= 50;
	windInfo.windowPosY		= 50;
	windInfo.windowWidth	= 1280;
	windInfo.windowHeight	= 720;

	/*
	AllocConsole();
	SetConsoleTitleA("Debug Console");
	Win32DebugConsolePrint("Hello World!\n");
	*/

	if (!Win32CreateApplication(hInstance, appInfo, &windClass))
	{
		Win32DebugConsolePrint("Win32CreateApplication failed!");
		DWORD error = GetLastError();
		Win32ForceKillApplication(PLATFORM_EXIT_ERROR);
		return PLATFORM_EXIT_ERROR;
	}

	if (!win32CreateWindow(hInstance, windClass, windInfo, &wind))
	{
		Win32DebugConsolePrint("Win32CreateWindow failed!");
		DWORD error = GetLastError();
		Win32ForceKillApplication(PLATFORM_EXIT_ERROR);
		return PLATFORM_EXIT_ERROR;
	}

	ShowWindow(wind, nCmdShow);

	Win32LoadWyvernCore();

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SwapBuffers(GetDC(wind));

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}