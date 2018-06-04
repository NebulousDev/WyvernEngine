
#define WIN32_LEAN_AND_MEAN	1
#define NOCOMM				1

#include <Windows.h>
#include <Core\platform\platform.h>
#include "win32OpenGL.h"
#include <iostream>

#include <GLEW\GL\glew.h>

/*=================================================================
|	GLOBAL VARS                                                   |
=================================================================*/

// TODO: I dont like globals

static WNDCLASS		sWindClass		= {};
static HWND			sWindow			= NULL;
static HDC			sDevice			= NULL;

#if defined(GFXAPI_OPENGL_ENABLED)

static bool			sGLInitialized	= false;
static GLContext	sGLContext		= NULL;

#endif


/*=================================================================
|	FUNCTIONS                                                     |
=================================================================*/

// LoadPlatformFunctions
typedef int32							(*fLoadPlatformFunctions)(PlatformFuncs funcs);
static fLoadPlatformFunctions			sLoadPlatformFunctionsFunc;
#define LoadPlatformFunctions(funcs)	sLoadPlatformFunctionsFunc(funcs)

// UpdateAndRender
typedef	void							(*fUpdateAndRender)();
static fUpdateAndRender					sUpdateAndRenderFunc;
#define UpdateAndRender()				sUpdateAndRenderFunc()

/////////////////////////////////////////////////////////////////////////////////////////

int32 Win32OpenGLCreateContext()
{
	sGLContext = GLCreateContext(sDevice);

	if (!sGLContext) return WYVERN_ERROR;

	if (InitOpenGL() == WYVERN_SUCCESS)
		sGLInitialized = true;

	return WYVERN_SUCCESS;
}

int32 Win32OpenGLMakeContextCurrent()
{
	return GLMakeContextCurrent(sDevice, sGLContext) 
		== WYVERN_SUCCESS ? WYVERN_SUCCESS : WYVERN_ERROR;
}

/*=================================================================
|	WIN32 MEMORY                                                  |
=================================================================*/

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

/*=================================================================
|	WIN32 APPLICATION                                             |
=================================================================*/

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

int32 Win32LoadWyvernCore()
{
	HMODULE wyvernCoreDll = LoadLibrary("wyverncore.dll");

	sLoadPlatformFunctionsFunc = (fLoadPlatformFunctions)GetProcAddress(wyvernCoreDll, "LoadPlatformFunctions");
	sUpdateAndRenderFunc = (fUpdateAndRender)GetProcAddress(wyvernCoreDll, "UpdateAndRender");

	PlatformFuncs funcs = {};

#if defined(GFXAPI_OPENGL_ENABLED)
		funcs.funcOpenGLCreateContext = &Win32OpenGLCreateContext;
	funcs.funcOpenGLMakeContextCurrent = &Win32OpenGLMakeContextCurrent;
#endif

	LoadPlatformFunctions(funcs);

	return WYVERN_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////////////

/*=================================================================
|	WIN32 WINDOW CALLBACK                                         |
=================================================================*/

LRESULT CALLBACK Win32WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			sDevice = GetDC(hwnd);
			/*
			sGLContext = GLCreateContext(sDevice);

			if (!sGLContext)
			{
				Win32DebugConsolePrint("Failed to create glContext!");
			}

			if (!InitOpenGL())
			{
				Win32DebugConsolePrint("Failed to init GLEW!");
			}
			*/

			return 0;
		}

		case WM_DESTROY:
		{
			GLDeleteContext(sGLContext);
			Win32ExitApplication(PLATFORM_EXIT_PEACEFULL);
			return 0;
		}

		case WM_PAINT:
		{
			UpdateAndRender();
			SwapBuffers(sDevice);
			return 0;
		}

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/*=================================================================
|	WIN32 CREATE APPLICATION                                      |
=================================================================*/

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

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
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

	if (!Win32CreateApplication(hInstance, appInfo, &sWindClass))
	{
		Win32DebugConsolePrint("Win32CreateApplication failed!");
		DWORD error = GetLastError();
		Win32ForceKillApplication(PLATFORM_EXIT_ERROR);
		return PLATFORM_EXIT_ERROR;
	}

	if (!win32CreateWindow(hInstance, sWindClass, windInfo, &sWindow))
	{
		Win32DebugConsolePrint("Win32CreateWindow failed!");
		DWORD error = GetLastError();
		Win32ForceKillApplication(PLATFORM_EXIT_ERROR);
		return PLATFORM_EXIT_ERROR;
	}

	ShowWindow(sWindow, nCmdShow);

	Win32LoadWyvernCore();

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}