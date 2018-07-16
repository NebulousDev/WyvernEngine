#pragma once
#include "win32.h"
#include "platform.h"

typedef RESULT(*CreateFunc)(ApplicationInfo* info);
typedef RESULT(*StartFunc)(const Application* app, const Platform* platform);
typedef RESULT(*LoopFunc)(const Application* app);

class Runtime
{
private:

	HMODULE		instance;
	CreateFunc	fpCreate;
	StartFunc	fpStart;
	LoopFunc	fpLoop;

	Runtime()	{}

	friend Runtime* CreateRuntime(const char* dll);
	friend void		DestroyRuntime(Runtime* runtime);

public:

	RESULT Create(ApplicationInfo* info);
	RESULT Start(const Application* app, const Platform* platform);
	RESULT Loop(const Application* app);
};

Runtime* CreateRuntime(const char* dll);

void DestroyRuntime(Runtime* runtime);