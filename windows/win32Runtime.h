#pragma once
#include <platform\runtime.h>

class Win32Runtime : public Runtime
{
	friend Runtime*		Win32CreateRuntime(const char* dll);
	friend void			Win32FreeRuntime(Runtime* runtime);
};

class Win32CoreRuntime : public CoreRuntime
{
	friend CoreRuntime* Win32CreateCoreRuntime(const char* dll);
};

void*			Win32GetRuntimeFunction(Runtime* runtime, const char* func);
Runtime*		Win32CreateRuntime(const char* dll);
CoreRuntime*	Win32CreateCoreRuntime(const char* dll);
void			Win32FreeRuntime(Runtime* runtime);