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

//TODO: I Don't like global variables
static GraphicsContext*	sContext;
static GraphicsDevice*	sDevice;

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

	state->gfxDevice = GetDC(state->window);

	////////////////////////////////////////////////////////////////////////////////////

	PlatformApplication application = {};
	application.mPlatformOS = OS_WINDOWS;

	state->platformApp = &application;

	sContext = &state->gfxContext;
	sDevice = &state->gfxDevice;

	typedef bool32(*FuncGLIsContextCreated)();
	typedef RESULT(*FuncGLCreateContext)();
	typedef RESULT(*FuncGLDestroyContext)();
	typedef RESULT(*FuncGLEnableContext)();
	typedef RESULT(*FuncGLDisableContext)();
	typedef RESULT(*FuncGLSetContextCurrent)();

	//TODO: This is clever... BUT REALLY BAD

	PlatformGraphics graphics = {};
	graphics.fpGLIsContextCreated = (FuncGLIsContextCreated)([](void) { return *sContext != NULL; });
	graphics.fpGLCreateContext = (FuncGLCreateContext)([](void) { return GLCreateContext(sContext, *sDevice); });
	graphics.fpGLDestroyContext = (FuncGLDestroyContext)([](void) { return GLDeleteContext(sContext); });
	graphics.fpGLSetContextCurrent = (FuncGLSetContextCurrent)([](void) { return GLMakeContextCurrent(*sDevice, *sContext); });

	state->platformGfx = &graphics;

	////////////////////////////////////////////////////////////////////////////////////

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