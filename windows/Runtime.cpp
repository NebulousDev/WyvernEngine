#include "Runtime.h"
#include <iostream>

RESULT Runtime::Create(ApplicationInfo* info)
{
	return fpCreate(info);
}

RESULT Runtime::Start(const Application* app, const Platform* platform)
{
	return fpStart(app, platform);
}

RESULT Runtime::Loop(const Application* app)
{
	return fpLoop(app);
}

Runtime* CreateRuntime(const char* dll)
{
	HINSTANCE instance = LoadLibrary(dll);

	if (!instance)
	{
		std::cout << "Error: Unable to locate runtime '" << dll << "'" << std::endl;
		return NULLPTR;
	}

	Runtime* runtime	= new Runtime();
	runtime->instance	= instance;
	runtime->fpCreate	= (CreateFunc)GetProcAddress(instance, "Create");
	runtime->fpStart	= (StartFunc)GetProcAddress(instance, "Start");
	runtime->fpLoop		= (LoopFunc)GetProcAddress(instance, "Loop");

	return runtime;
}

void DestroyRuntime(Runtime* runtime)
{
	bool8 free = FreeLibrary(runtime->instance);
	delete runtime;
}
