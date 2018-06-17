#pragma once
#include "common.h"
#include "platform.h"

class Runtime
{
private:
	typedef RESULT(*FuncTypeCreate)(const PlatformApplication* application, const PlatformGraphics* graphics);
	typedef void(*FuncTypeUpdate)();
	typedef void(*FuncTypeDestroy)();

	FuncTypeCreate	fpCreate;
	FuncTypeUpdate	fpUpdate;
	FuncTypeDestroy fpDestroy;

	HMODULE mRuntime;

public:
	RESULT CreateRuntime(const Win32State* state, const char* dll);
	RESULT DestroyRuntime();

	INLINE RESULT	Create(const PlatformApplication* application, const PlatformGraphics* graphics) { return fpCreate(application, graphics); }
	INLINE void		Update() { fpUpdate(); }
	INLINE void		Destroy() { fpDestroy(); }
};

RESULT RunApplication(Win32State* state, ApplicationInfo* appInfo, WindowInfo* windInfo);
