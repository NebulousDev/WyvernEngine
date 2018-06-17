#include "runtime.h"

LRESULT CALLBACK HandleEvents(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static Win32State* state = {};
	static Runtime* runtime = {};

	switch (uMsg)
	{
		case STARTUP_STATE_MESSAGE:
		{
			state = (Win32State*)wParam;
			return 0;
		}

		case NEW_RUNTIME_MESSAGE:
		{
			runtime = (Runtime*)wParam;
			runtime->Create(state->platformApp, state->platformGfx);
			return 0;
		}

		case WM_DESTROY:
		{
			state->running = false;
			PostQuitMessage(0);
			runtime->Destroy();
			runtime->DestroyRuntime();
			return 0;
		}

		case WM_PAINT:
		{
			runtime->Update();
			SwapBuffers(state->gfxDevice);
			return 0;
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, PWSTR args, int show)
{
	static Win32State state = {};
	state.instance			= instance;
	state.arguments			= args;
	state.show				= show;

	static ApplicationInfo appInfo = {};
	appInfo.appName			= "WyvernGame";
	appInfo.appVersion		= "1.0.0";

	static WindowInfo windInfo = {};
	windInfo.windowTitle	= "Wyvern Game";
	windInfo.windowPosX		= 50;
	windInfo.windowPosY		= 50;
	windInfo.windowWidth	= 1280;
	windInfo.windowHeight	= 720;

	return RunApplication(&state, &appInfo, &windInfo);
}