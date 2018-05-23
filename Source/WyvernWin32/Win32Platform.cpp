
#define WIN32_LEAN_AND_MEAN
#define NOCOMM

#include "Win32Platform.h"
#include <Windows.h>
#include <iostream>

LRESULT CALLBACK Win32WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

		case WM_DESTROY:
		{
			ExitApplication(PLATFORM_EXIT_PEACEFULL);
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

int32 GLOBAL Win32CreateWindow(HINSTANCE instance, WNDCLASS windClass, WindowInfo info, HWND* wind)
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

int32 GLOBAL Win32AllocPage(const uint32 pages)
{
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

int32 GLOBAL ExitApplication(int32 code)
{
	PostQuitMessage(code);
	return code;
}

int32 GLOBAL ForceKillApplication(int32 code)
{
	// TODO: implement ForceKillApplication
	return code;
}

void GLOBAL DebugConsolePrint(const char* text)
{
	DWORD charsWritten;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), text, strlen(text), &charsWritten, NULL);
}

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

	AllocConsole();
	SetConsoleTitleA("Debug Console");
	DebugConsolePrint("Hello World!\n");

	if (!Win32CreateApplication(hInstance, appInfo, &windClass))
	{
		DebugConsolePrint("Win32CreateApplication failed!");
		DWORD error = GetLastError();
		ForceKillApplication(PLATFORM_EXIT_ERROR);
		return PLATFORM_EXIT_ERROR;
	}

	if (!Win32CreateWindow(hInstance, windClass, windInfo, &wind))
	{
		DebugConsolePrint("Win32CreateWindow failed!");
		DWORD error = GetLastError();
		ForceKillApplication(PLATFORM_EXIT_ERROR);
		return PLATFORM_EXIT_ERROR;
	}

	ShowWindow(wind, nCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}