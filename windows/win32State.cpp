#include "win32State.h"

static Win32State* sWin32State;

void InitWin32State(Win32State* state)
{
	sWin32State = state;
}

const Win32State* GetWin32State()
{
	return sWin32State;
}
