#include "runtime.h"

extern LRESULT CALLBACK HandleEvents(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

RESULT Runtime::CreateRuntime(const Win32State* state, const char* dll)
{
	mRuntime = LoadLibrary(dll);

	if (!mRuntime)
	{
		MessageBox(state->window, "Error creating runtime.", "Error", MB_OK);
		return WYVERN_ERROR;
	}

	fpCreate = (FuncTypeCreate)GetProcAddress(mRuntime, "Create");
	fpUpdate = (FuncTypeUpdate)GetProcAddress(mRuntime, "Update");
	fpDestroy = (FuncTypeDestroy)GetProcAddress(mRuntime, "Destroy");

	if (!fpCreate || !fpUpdate || !fpDestroy)
	{
		MessageBox(state->window, "Error creating runtime. Failed to retrieve function pointers.", "Error", MB_OK);
		return WYVERN_ERROR;
	}

	return WYVERN_SUCCESS;
}

RESULT Runtime::DestroyRuntime()
{
	FreeLibrary(mRuntime);
	fpCreate	= NULL;
	fpUpdate	= NULL;
	fpDestroy	= NULL;
	return WYVERN_SUCCESS;
}

//TODO: Tidy up RunApplication
RESULT RunApplication(Win32State* state, ApplicationInfo* appInfo, WindowInfo* windInfo)
{
	/*
	AllocConsole();
	SetConsoleTitleA("Debug Console");
	Win32DebugConsolePrint("Hello World!\n");
	*/

	state->windClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	state->windClass.lpszClassName = appInfo->appName;
	state->windClass.hInstance = state->instance;
	state->windClass.lpfnWndProc = &HandleEvents;

	state->gfxDevice = GetDC(state->window);

	if (!RegisterClass(&state->windClass))
	{
		MessageBox(state->window, "Error creating application. Error Code: [DO LATER]", "Error", MB_OK);
		return WYVERN_ERROR;
	}

	state->window = CreateWindowEx
	(
		0, state->windClass.lpszClassName,
		windInfo->windowTitle,
		WS_OVERLAPPEDWINDOW,
		windInfo->windowPosX, windInfo->windowPosY,
		windInfo->windowWidth, windInfo->windowHeight,
		NULL, NULL, state->instance, NULL
	);

	if (state->window == NULL)
	{
		DWORD error = GetLastError();
		MessageBox(state->window, "Error creating window. Error Code: [DO LATER]", "Error", MB_OK);
		return WYVERN_ERROR;
	}

	Runtime runtime;
	RESULT runtimeResult = runtime.CreateRuntime(state, CORE_DLL_NAME);

	if (runtimeResult == WYVERN_ERROR)
		return WYVERN_ERROR;

	////

	PlatformApplication application = {};
	application.mPlatformOS = OS_WINDOWS;

	state->platformApp = &application;

	PlatformGraphics graphics = {};
	graphics.fpGLCreateContext = NULL;

	state->platformGfx = &graphics;

	////

	HandleEvents(state->window, STARTUP_STATE_MESSAGE, (WPARAM)state, (LPARAM)state);
	HandleEvents(state->window, NEW_RUNTIME_MESSAGE, (WPARAM)&runtime, (LPARAM)&runtime);

	ShowWindow(state->window, state->show);

	state->running = true;

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return WYVERN_SUCCESS;
}