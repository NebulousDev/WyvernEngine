#include "win32.h"
#include "win32Runtime.h"
#include <iostream>

void* Win32GetRuntimeFunction(Runtime* runtime, const char* func)
{
	return (void*)GetProcAddress((HINSTANCE)runtime->GetInstance(), func);
}

Runtime* Win32CreateRuntime(const char* dll)
{
	HINSTANCE instance = LoadLibrary(dll);

	if (!instance)
	{
		std::cout << "Error: Failed to locate runtime dll '" << dll << "'." << std::endl;
		return NULLPTR;
	}

	Win32Runtime* wRuntime	= new Win32Runtime();
	wRuntime->mInstance		= instance;
	wRuntime->fpGetFunction = Win32GetRuntimeFunction;
	return wRuntime;
}

CoreRuntime* Win32CreateCoreRuntime(const char* dll)
{
	HINSTANCE instance = LoadLibrary(dll);

	if (!instance)
	{
		std::cout << "Error: Failed to locate core runtime dll '" << dll << "'." << std::endl;
		return NULLPTR;
	}

	Win32CoreRuntime* wCoreRuntime	= new Win32CoreRuntime();
	wCoreRuntime->mInstance			= instance;
	wCoreRuntime->fpGetFunction		= Win32GetRuntimeFunction;

	wCoreRuntime->fpCreate	= (CoreRuntime::CreateFunc)Win32GetRuntimeFunction(wCoreRuntime, "Create");
	wCoreRuntime->fpStart	= (CoreRuntime::StartFunc)Win32GetRuntimeFunction(wCoreRuntime, "Start");
	wCoreRuntime->fpLoop	= (CoreRuntime::LoopFunc)Win32GetRuntimeFunction(wCoreRuntime, "Loop");

	/*
	wCoreRuntime->fpCreate	= wCoreRuntime->GetFunction<CoreRuntime::CreateFunc>("Create");
	wCoreRuntime->fpStart	= wCoreRuntime->GetFunction<CoreRuntime::StartFunc>("Start");
	wCoreRuntime->fpLoop	= wCoreRuntime->GetFunction<CoreRuntime::LoopFunc>("Loop");
	*/

	// TODO: assert these ^ are not null

	return wCoreRuntime;
}

void Win32FreeRuntime(Runtime* runtime)
{
	Win32Runtime* wRuntime = (Win32Runtime*)runtime;
	FreeLibrary((HINSTANCE)wRuntime->mInstance);
	delete wRuntime;
}